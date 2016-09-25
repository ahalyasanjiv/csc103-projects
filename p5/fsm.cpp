/*
 * CSc103 Project 5: Syntax highlighting, part one.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 * I asked two classmates (Jamie Fung and Jane Chen) for help on
 * an error that I was stuck on.
 * Jamie told me that I accidentally put a '/' instead of a
 * '\' at one point in my code. Jane told me that I did not have to
 * redefine INSET in this file since it was already defined in the
 * header file.
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:3
 */

#include "fsm.h"
using namespace cppfsm;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// make sure this function returns the old state.  See the header
// file for details.
int cppfsm::updateState(int& state, char c) {

       int oldState = state;
				switch(state){

						case start:
								if(c=='/')
										state = readfs;
								else if (c == '"')
										state = strlit;
								else if(INSET(c,ident_st))
										state = scanid;
								else if (INSET(c,num))
										state = scannum;
								else if (INSET(c,iddelim))
										state = start;
                break;

						case scanid:
								if(c=='/')
										state = readfs;
								else if (c == '"')
										state = strlit;
								else if(INSET(c,ident_st))
										state = scanid;
								else if (INSET(c,iddelim))
										state = start;
                break;

						case comment:
								state = comment;
                break;

						case strlit:
								if (c == '"')
										state = start;
								else if (c=='\\')
										state = readesc;
								else
										state = strlit;
                break;

						case readfs:
								if (INSET(c,ident_st))
										state = scanid;
								else if (c=='/')
										state = comment;
								else if (c=='"')
										state = strlit;
								else if (INSET(c,num))
										state = scannum;
                break;

						case readesc:
								if (INSET(c,escseq))
										state = strlit;
								else
										state = error;
                break;

						case scannum:
								if (INSET(c,num))
										state = scannum;
                else if (INSET(c,iddelim))
                    state = start;
                else if (c=='/')
                    state = readfs;
								else
										state = error;
                break;

						case error:
                state=error;
                break;

				}
	return oldState;
}

