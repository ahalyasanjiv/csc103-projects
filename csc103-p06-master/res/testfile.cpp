#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <map>
using std::map;
#include <initializer_list> // for setting up maps without constructors.

// usually global variables are a bad thing, but for simplicity,
// we'll make an exception here.

// initialize our map with the keywords from our list:
map<string, short> reserved = {
#include "keywords.txt"
};
// note: this is not a very standard use of #include...

int main() {
	//do stuff
	int x = 77;
	int y = x * 91;
	cout << "this is super fun.\n";
	cout << ":D\n";
	cout << "let's make sure comments // in strings are strings\n";
	// and that "strings" in comments are "comments"
	cout << "a bad escape: \o causes errors";
	// could also have errors parsing numeric constants:
	cout << 99ZXY;
	return 0;
}
