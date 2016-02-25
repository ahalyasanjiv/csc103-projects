/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * http://stackoverflow.com/questions/5811151/why-do-we-check-upto-the-square-root-of-a-prime-number-to-determine-if-it-is-pri
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>

int main()
{
	unsigned long n;

	while (cin>>n){

			int primeTest=0; /*Value of this variable tells if prime or not*/
			if (n==2)				 /*If 2, then prime */
					primeTest=1;

			/* Test odd #s for primality */
			if (n%2!=0){

					/*If greater than 1 & less than or equal to 7, then prime */
					if (n>1 && n<=7)
						primeTest=1;

					/*If greater than 7, test if odd integers until
						sqrt are a factor*/
					else {
							for (int testFactor=3;testFactor<=sqrt(n);testFactor+=2){
									if (n%testFactor==0){
											primeTest=0;
											break;
									}
									else
											primeTest=1;
							}
					}

			}
			cout<<primeTest<<"\n";
	}
	return 0;
}

