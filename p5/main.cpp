#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "fsm.h"
using namespace cppfsm;

void testFSM(string s) {
	cout << s << endl;
	int cstate = start;
	for (unsigned long i = 0; i < s.length(); i++) {
		cout << updateState(cstate,s[i]);
	}
	cout << cstate << endl; // print the last state
}

int main() {
	/* you can run your own tests here, but keep the loop
	 * below, as that is used in the test script. */

	// read one line at a time, and feed it through
	// the finite state machine:
	string input;
	while(getline(cin,input)) {
		cout << " ";
		testFSM(input);
	}
	return 0;
}
