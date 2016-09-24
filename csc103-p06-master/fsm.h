/*
 * File fsm.h.
 * Header file containing prototypes and constants for finite state
 * machine to scan (limited) C++ syntax.
*/
#pragma once  // make sure symbols below are only defined once.

#include <string>
using std::string;
#include <set>
using std::set;
#include <map>
using std::map;
#include <initializer_list> // for setting up maps without constructors.


// we'll put all of our code in a namespace; this gives every symbol
// you see below a last name of "cppfsm".  In other code, if you don't
// do a "using namespace fsm;", then you will have to use the full
// (first and last) name, e.g. cppfsm::variablename
// Why would you do this, you ask??  Well, it is actually being nice
// to other programmers that use our code.  This will reduce the chances
// of collisions with the other files that they are importing.
namespace cppfsm {
	/*            constants             */
	// character classes:
	const string s_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const string s_num = "0123456789";
	const string s_idst = "#_" + s_alpha;
	const string s_id = s_num + s_idst;
	const string s_escseq = "abfnrtvx?\'\"\\";
	const string s_iddelim = "~!%^&*()-+=;:{}[]<>|\\.,? \t\n\r";
	const set<char> num(s_num.c_str(),s_num.c_str()+s_num.length());
	const set<char> alpha(s_alpha.c_str(),s_alpha.c_str()+s_alpha.length());
	const set<char> ident_st(s_idst.c_str(),s_idst.c_str()+s_idst.length());
	const set<char> ident(s_id.c_str(),s_id.c_str()+s_id.length());
	const set<char> escseq(s_escseq.c_str(),s_escseq.c_str()+s_escseq.length());
	const set<char> iddelim(s_iddelim.c_str(),s_iddelim.c_str()+s_iddelim.length());

	/* NOTE: to ease the pain of checking membership in sets, you could
	 * write something like this: */
	#define INSET(x,S) (S.find(x) != S.end())
	/* and then for example, to check if a character c is
	 * in the ident set, you could write:
	 * if (INSET(c,ident))
	 *    cout << c << " was in the set ident\n";
	 * */


	// an enumeration for our states.  Please refer to the diagram to
	// make sense of all this.
	// Note: The "enum" construct is just a convenient way to set up some
	// constant integers.  It would be (more or less) the same to say:
	// const unsigned int normal=0,comment=1,...  and so on.
	enum states {
		start,   // the start state
		scanid,  // we are in the middle of scanning an identifier
		comment, // we are scanning a comment
		strlit,  // we're scanning a string literal (double quotes: "")
		readfs,  // just read forward slash while scanning a numeric constant
				 // or identifier, or from the start state.
		readesc, // just read backslash from strlit state (start of escape seq)
		scannum, // in the middle of scanning a numeric constant
		error    // error state; read a messed up numeric or escape sequence.
	};

	/*            functions             */
	// the finite state machine.  takes in a state and a
	// character, and updates the state.  @return: gives
	// you the old value of the state.
	int updateState(int& state, char c);
}
