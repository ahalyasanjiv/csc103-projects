/*
 * CSc103 Project 4: Triangles
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * 		Heron's Formula - https://en.wikipedia.org/wiki/Heron%27s_Formula
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:
 *
 * Ahalya 1
 * Jamie 	1
 * Jane		1.5
 * ______________
 * Total:	3.5
 */

#include "triangles.h" // import the prototypes for our triangle class.
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <cmath>

// note the "triangle::" part.  We need to specify the function's
// FULL name to avoid confusion.  Else, the compiler will think we
// are just defining a new function called "perimeter"
unsigned long triangle::perimeter() {
	return s1+s2+s3;
}

unsigned long triangle::area() {
	// TODO: write this function.
	// Note: why is it okay to return an integer here?  Recall that
	// all of our triangles have integer sides, and are right triangles...
#if 0
	/* ==== BASE * HEIGHT METHOD ==== */
		// for right triangles only
	unsigned long  hypotenuse = s1;
	if (s2 > hypotenuse)
		hypotenuse = s2;
	if (s3 > hypotenuse)
		hypotenuse = s3;

	return (s1 * s2 * s3) /(hypotenuse * 2);

#else
	/* ==== HERON'S FORMULA ==== */
		// for all triangles
	unsigned long semip = perimeter()/2;
	unsigned long A = sqrt(semip*(semip-s1)*(semip-s2)*(semip-s3));

	return A;

#endif
}

void triangle::print() {
	cout << "[" << s1 << "," << s2 << "," << s3 << "]";
}

bool congruent(triangle t1, triangle t2) {
	// TODO: write this function.

	// store sides of each triangle into an array
	unsigned long sidesT1[3] = {t1.s1,t1.s2,t1.s3};
	unsigned long sidesT2[3] = {t2.s1,t2.s2,t2.s3};

	// sort each triangle array
	sort(sidesT1, sidesT1+3);
	sort(sidesT2, sidesT2+3);

	// run for loop to check if sides are equal
	for (size_t i=0;i<3;i++){
		if (sidesT1[i]!=sidesT2[i]){
				return false;
		}
	}
	return true;
}

bool similar(triangle t1, triangle t2) {
	// TODO: write this function.

	// store sides of each triangle into an array
	double sidesT1[3] = {t1.s1,t1.s2,t1.s3};
	double sidesT2[3] = {t2.s1,t2.s2,t2.s3};

	// sort each triangle array
	sort(sidesT1, sidesT1+3);
	sort(sidesT2, sidesT2+3);

	// store ratio of smallest sides of the 2 triangles
	double ratio = sidesT1[0]/sidesT2[0];

	// compare ratios of rest of corresponding sides to check if the 2 triangles are similar
	for (size_t i=1; i<3;i++){
		if(sidesT1[i]/sidesT2[i]!=ratio){
				return false;
		}
	}
	return true;

}

vector<triangle> findRightTriangles(unsigned long l, unsigned long h) {
	// TODO: find all the right triangles with integer sides,
	// subject to the perimeter bigger than l and less than h
	vector<triangle> retval; // storage for return value.

	for (unsigned long i = 1; i < h; i++) {
		for (unsigned long j = 1; j < h; j++) {
			for (unsigned long k = 1; k < h; k++) {
				triangle t = triangle(i,j,k);

				// perimeter must be within bounds
				if (t.perimeter() >= l && t.perimeter() <= h) {
					unsigned long sides[3] = {i,j,k};
					sort(sides,sides + 3); // order the sides --> hypotenuse = side[2]
					// check if the triangle is a right triangle
					// using a^2 + b^2 = c^2
					if (sides[0]*sides[0] + sides[1]*sides[1] == sides[2]*sides[2]) {
						bool inVector = false;
						// check if the triangle is already in the vector
						for (size_t i = 0; i < retval.size(); i++) {
							if (congruent(retval[i],t)) {
								inVector = true;
								break; // triangle is found in vector, stop
							}
						}
						if (!inVector) {
							retval.push_back(t); // add triangle to vector
						}
					}
				}
			}
		}
	}
	return retval;
}