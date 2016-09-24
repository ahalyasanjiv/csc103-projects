/*
 * triangles.h
 * Header file for triangle class.
*/
// make sure this file is not included multiple times:
#pragma once

#include <vector>
using std::vector;

class triangle {
	public:
		// member functions:
		// constructor:
		triangle(unsigned long a=3, unsigned long b=4, unsigned long c=5):
			s1(a),s2(b),s3(c) {}
		unsigned long perimeter();
		unsigned long area();
		void print();  // prints to standard output
		// member variables:
		// integers for the 3 sides:
		unsigned long s1;
		unsigned long s2;
		unsigned long s3;
};

vector<triangle> findRightTriangles(unsigned long l, unsigned long h);
bool congruent(triangle t1, triangle t2);
bool similar(triangle t1, triangle t2);
