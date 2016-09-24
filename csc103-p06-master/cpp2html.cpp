/*
 * CSc103 Project 6: Syntax highlighting, part two.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
 * http://ubuntuforums.org/showthread.php?t=396479
 * www.dreamincode.net/forums/topic/42209-c-strings/
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * Total #hours: 11 hours
 * 		Planning on paper: 4 hours
 * 		Coding: 7 hours
 * 		(Jane: 2 hours, Jamie: 3 hours, Ahalya: 2 hours)
 */

#include "fsm.h"
using namespace cppfsm;
#include <iostream>
#include <sstream> // using this to convert string to int
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <set>
using std::set;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <initializer_list> // for setting up maps without constructors.

// enumeration for our highlighting tags:
enum {
	hlstatement,  // used for "if,else,for,while" etc...
	hlcomment,    // for comments
	hlstrlit,     // for string literals
	hlpreproc,    // for preprocessor directives (e.g., #include)
	hltype,       // for datatypes and similar (e.g. int, char, double)
	hlnumeric,    // for numeric literals (e.g. 1234)
	hlescseq,     // for escape sequences
	hlerror,      // for parse errors, like a bad numeric or invalid escape
	hlident       // for other identifiers.  Probably won't use this.
};

// usually global variables are a bad thing, but for simplicity,
// we'll make an exception here.
// initialize our map with the keywords from our list:
map<string, short> hlmap = {
#include "res/keywords.txt"
};
// note: the above is not a very standard use of #include...

// map of highlighting spans:
map<int, string> hlspans = {
	{hlstatement, "<span class='statement'>"},
	{hlcomment, "<span class='comment'>"},
	{hlstrlit, "<span class='strlit'>"},
	{hlpreproc, "<span class='preproc'>"},
	{hltype, "<span class='type'>"},
	{hlnumeric, "<span class='numeric'>"},
	{hlescseq, "<span class='escseq'>"},
	{hlerror, "<span class='error'>"}
};
// note: initializing maps as above requires the -std=c++0x compiler flag,
// as well as #include<initializer_list>.  Very convenient though.
// to save some typing, store a variable for the end of these tags:
string spanend = "</span>";

string translateHTMLReserved(char c) {
	switch (c) {
		case '"':
			return "&quot;";
		case '\'':
			return "&apos;";
		case '&':
			return "&amp;";
		case '<':
			return "&lt;";
		case '>':
			return "&gt;";
		case '\t': // make tabs 4 spaces instead.
			return "&nbsp;&nbsp;&nbsp;&nbsp;";
		default:
			char s[2] = {c,0};
			return s;
	}
}

string translateHTMLContent (string s) {
	string translation;
	for (int i=0;i<s.length();i++){
		translation += translateHTMLReserved(s[i]);
	}
	return translation;
}

string fsm(string s){ //converts input string into fsm
	int cstate = start;
	string f = std::to_string(cstate);
	for (unsigned int i = 0 ; i < s.length(); i++) {
		updateState(cstate, s[i]);
		f += std::to_string(cstate);
	}
	f += cstate; //add on last state
	return f;
}

void printVector(vector<int> V) {
	for (int i = 0; i < V.size(); i++)
		cout << V[i] << "  "; // two spaces in case of double digit indexes
	cout << endl;
}

// not sure how to make this look nice
// when printing it out, the code is separated by |
void printVector(vector<string> V) {
	cout << "|";
	for (int i = 0; i < V.size(); i++)
		cout << V[i] << "|";
	cout << endl;
}

// takes fsm form of the input string
// returns a vector of starting indexes where the states change
vector<int> getIndexes(string fsm) {
	vector<int> V;
	V.push_back(0);
	int curState = 0; // the first state always starts as 0

	for (int i = 1; i < fsm.length(); i++) { // start at index 1
		string digit = fsm.substr(i,1); // number at index i (string)
		std::stringstream ss(digit);
		int temp;
		ss >> temp; // converting the string to an int in order to compare
					// temp is now the numbers at index i (int)
		if (curState != temp) {
			V.push_back(i); // add the starting index of the next state
			curState = temp; // update the current state
		}
	}
	return V;
}

// takes the fsm form of the input string and the vector of startIndexes
// returns a vector of the numerical state that it was changed to
vector<int> getStates(string fsm, vector<int> startIndexes) {
	vector<int> V;
	for (int i = 0; i < startIndexes.size(); i++) {
		string digit = fsm.substr(startIndexes[i],1); // number at the index
		std::stringstream ss(digit);
		int state;
		ss >> state;
		V.push_back(state); // add the state that it was changed to
	}
	return V;
}

// takes the original line (the input) and the vector of startIndexes
// returns a vector that breaks the pieces of the line apart according
// to what their state is
vector<string> getCode(string input, vector<int> startIndexes) {
	vector<string> V;
	int begin, end, length;
	int i;
	for (i = 0; i < startIndexes.size() - 1; i++) {
		begin = startIndexes[i];
		end = startIndexes[i + 1]; 	// index where the next state begins
		length = end - begin;	// length of the string where the state
									// remains the same
		string code = input.substr(begin,length);
		V.push_back(code);
	}
	// also add the code from the last state change to the end of the input
	begin = startIndexes[i];
	end = input.length();
	length = end - begin;
	string code = input.substr(begin,length);
	V.push_back(code);

	return V;
}

/* Do this when the state is statement(1). Take the vector containing the 
pieces of code and the index that that is in the comment state.
Return the HTML for the comment portion of the inputted line.*/
string statementToHTML(vector<string> V, int index) {
	// Trying to find whether statement, type, or preprocessor
	string openTag;
	string content = V[index];
	map<string,short>::iterator i;
	/* if the string is in the map as one of the keywords, 
	add appropriate tag */
	i = hlmap.find(content);
	if (i != hlmap.end()){
		openTag = hlspans[hlmap[content]];
		return openTag + translateHTMLContent(content) + spanend;
	}
	else
		return translateHTMLContent(content);
}

/* Do this when the state is readfs(4) and turns to comment(2).
Take the vector containing the pieces of code and the index that 
is in the comment state.
Return the HTML for the comment portion of the inputted line.
NOTE: code[index-1] will ALWAYS be a / and its state is readfs (4) */
string commentToHTML(vector<string> V, int index) {
	string openTag = hlspans[hlcomment];
	// first forward slash and everything after it
	string content = V[index] + V[index+1];
	return openTag + translateHTMLContent(content) + spanend;
}

/* Do this when the state is scannum(6). Take the vector containing the
pieces of code and the index that is in the scannum state.
Return the HTML for the numeric portion of the inputted line. */
string numericToHTML(vector<string> V, int index) {
	string openTag = hlspans[hlnumeric];
	string content = V[index]; // the numbers
	return openTag + translateHTMLContent(content) + spanend;
}

/* Do this when the state is strlit(3). Take the vector containing the
pieces of code and the index that is in the strlit state.
Return the HTML for the string portion of the inputted line.
NOTE: code[index+1] is the 2nd double quotes */
string stringToHTML(vector<string> V, int index) {
	string openTag = hlspans[hlstrlit];
	string content = V[index];

	// this happens if there is an escseq in the strlit
	if (content.substr(0,1) != "\"") { // if false, content does not change
		// gets rid of escseq part that was mistakenly in state strlit
		content = content.substr(1,content.length() - 1);
	}

	string endQuote; // end quotes are in the start state (0)
	string nextPart = V[index + 1]; // next portion of the code
									// which is in a different state
	// if the next part of the code starts with "
	if (nextPart.substr(0,1) == "\"") { // otherwise, endQuote remains empty
		endQuote = "\"";
	}

	return openTag + translateHTMLContent(content + endQuote) + spanend;
}

/* Do this when the state is start. Take the vector containing the pieces
of code and the index that is in the start state.
NOTE: I needed to make this function because the end quote for a string
is in the state start. This fuction makes sure that the end quote is not
printed out again for a second time by removing the ". */
string startToHTML(vector<string> V, int index) {
	string currPart = V[index];
	if (currPart.substr(0,1) == "\"") // disregard the quote
		currPart = currPart.substr(1,currPart.length() - 1);
	return translateHTMLContent(currPart);
}

/* Do this when the state turns from readesc(5) to an escseq (not 7).
 * Take the vector containing the pieces of code and the index that is
 * in the start state */
string escseqToHTML(vector<string> V, int index) {
	string content = V[index+1]; //takes first character of next string in vector
	content = V[index] + content.substr(0,1);

	string openTag = hlspans[hlescseq];

	return openTag + translateHTMLContent(content) + spanend;
}

/*Do this when the state turns from readesc(5)/scannum(6) to an error (7). */
string errorToHTML(vector<string> V, int index) {
	string content;
	if (V[index] == "\\") //if readesc
		content = V[index] + V[index+1]; // V[index] is backslash
	else //if scannum
		content = V[index +1]; //V[index + 1] is stuff after the numbers

	string openTag = hlspans[hlerror];

	return openTag + translateHTMLContent(content) + spanend;
}

int main() {
	// TODO: write the main program.
	// It may be helpful to break this down and write
	// a function that processes a single line, which
	// you repeatedly call from main().

	string input;
	string state;
	string output;

	while(getline(cin, input)) {
		state = fsm(input);
		// printing stuff out so we can see it
		input = " " + input;
		// cout << input << endl;
		// cout << state << endl;

		vector<int> index = getIndexes(state);
		vector<int> VStates = getStates(state,index);
		vector<string> code = getCode(input,index);
		// printVector(index);
		// printVector(VStates);
		// printVector(code);

		for (int i = 0 ; i < index.size(); i++) {
			//runs through the elements of the three vectors
			switch (VStates[i]) {
				case start: //0
					output = output + startToHTML(code, i);
					break;
				case scanid: //1
					output = output + statementToHTML(code, i);
					break;
				case comment: //2
					//do nothing
					break;
				case strlit: //3
					output = output + stringToHTML(code, i);
					break;
				case readfs: //4
					if(VStates[i +1] == 2) //if the next state is a 2 (comment)
						output = output + commentToHTML(code, i);
					else
						output = output + code[i];
					break;
				case readesc: //5
					if (VStates [i+1] != 7) //if the next state is not 7
						output = output + escseqToHTML(code,i);
					else
						output = output + errorToHTML(code,i);
					break;
				case scannum: //6
					if (VStates [i+1] != 7)
						output = output + numericToHTML(code, i);
					else
						output = output + numericToHTML(code, i) + errorToHTML(code,i);
					break;
			}
		}
		output.erase(0,1); //erase extra space in front of html
		cout << output << endl;
		output.clear(); //clears output after each line
	}

	return 0;
}
