#include "fsm.h"
using namespace cppfsm;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int cppfsm::updateState(int& state, char c) {
	int oldstate = state;

	// for our simplified syntax, we always return to the
	// start state on a new line:
	if (c == '\n') {
		state = start;
		return oldstate;
	}

	switch (state) {
		case start:
			if (INSET(c,num))
				state = scannum;
			else if (INSET(c,ident_st))
				state = scanid;
			else if (c == '"')
				state = strlit;
			else if (c == '/')
				state = readfs;
			break;
		case scanid:
			if (INSET(c,iddelim))
				state = start;
			else if (c == '/')
				state = readfs;
			else if (c == '"')
				state = strlit;
			break;
		case scannum:
			if (INSET(c,iddelim))
				state = start; 
			else if (INSET(c,num))
				state = scannum; // don't change state.
			else if (c == '/')
			    state = readfs;
			else if (c == '"')
				state = strlit;
			else
				state = error;
			break;
		case readfs:
			if (INSET(c,ident_st))
				state = scanid;
			else if (INSET(c,num))
				state = scannum; 
			else if (c == '/')
				state = comment;
			else if (c == '"')
				state = strlit;
			break;
		case comment:
			break;
		case strlit:
			if (c == '\\')
				state = readesc;
			else if (c == '"')
				state = start;
			break;
		case readesc:
			if (INSET(c,escseq))
				state = strlit;
			else
				state = error;
			break;

		default:  // this is the error state.
			// For now, we'll just stay in the error state until
			// the end of the line.  Another (possibly more reasonable)
			// alternative is to jump back to the start or string state
			// after a character or two.
			break;
	}
	return oldstate;
}

