/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
    http://joelverhagen.com/blog/2010/11/taking-string-input-in-c-command-line/
 *
 */

#include <iostream> // Access to standard input and output
using std::cin;
using std::cout;
#include <string> // Provides string class
using std::string;

int main()
{
  // Asking for user's name
  cout << "Enter your name:\n";
  // Storing user's name
  string name;
  cin >> name;
  // Asking for relative's name
  cout << "Enter a relative:\n";
  // Storing relative's name
  string relative;
  cin >> relative;
  // Prints greeting at the end
  cout << "Hello. My name is " << name << ". You killed my "
  << relative << ". Prepare to die.\n";
  return 0;
}
