#include "triangles.h"
#include <cstdio>
#include <iostream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
#include <algorithm>
using std::sort;
using std::min;

struct tricompare
{
	bool operator()(const triangle& t1, const triangle& t2) {
		unsigned long ss1[3] = {t1.s1,t1.s2,t1.s3};
		sort(ss1,ss1+3);
		unsigned long ss2[3] = {t2.s1,t2.s2,t2.s3};
		sort(ss2,ss2+3);
		unsigned long i=0;
		while (ss1[i] == ss2[i]) i++;
		return (i!=3 && ss1[i] < ss2[i]);
	}
} tcmp;

void printSorted(const triangle& t, ostream& o = cout)
{
	unsigned long sides[3] = {t.s1,t.s2,t.s3};
	sort(sides,sides+3);
	o << "[" << sides[0] << "," << sides[1] << "," << sides[2] << "]";
}

istream& operator>>(istream& i, triangle& t)
{
	return (i >> t.s1 >> t.s2 >> t.s3);
}

ostream& operator<<(ostream& o, const triangle& t)
{
	return (o << "[" << t.s1 << "," << t.s2 << "," << t.s3 << "]");
}

void similarTest(const triangle& t1, const triangle& t2)
{
	cerr << "\nTesting " << t1 << " and " << t2 << "\n";
	cout << similar(t1,t2);
}

void congruentTest(const triangle& t1, const triangle& t2)
{
	cerr << "\nTesting " << t1 << " and " << t2 << "\n";
	cout << congruent(t1,t2);
}

int main(int argc, const char *argv[])
{
	const unsigned long nTests = 6;
	unsigned long tests[][2] = {{1,25},{1,30},{20,40},{30,75},{50,100},{75,125}};
	vector<triangle> v;
	for (unsigned long i = 0; i < nTests; i++) {
		fprintf(stderr, "Testing the range [%lu,%lu]...\n",tests[i][0],tests[i][1]);
		v = findRightTriangles(tests[i][0],tests[i][1]);
		sort(v.begin(), v.end(), tcmp);
		for (unsigned long j = 0; j < v.size(); j++) {
			printSorted(v[j]);
		}
		cout << "\n@";
	}
	// now test the area function
	unsigned long ta[][3] = {{23,29,18},{27,29,39},{43,38,91},{3,15,17},{32,77,38}};
	unsigned long t[3];
	unsigned long p = 23, g=5, x=1;
	unsigned long j,k,l;
	for (unsigned long i = 0; i < 5; i++) {
		x = x*g % p;
		j = x % 3;
		k = (j+1)%3;
		l = (k+1)%3;
		t[j] = ta[i][k]*ta[i][k] + ta[i][l]*ta[i][l];
		t[k] = 2*ta[i][k]*ta[i][l];
		t[l] = min(ta[i][k],ta[i][l]);
		t[l] = t[j] - 2*t[l]*t[l];
		x = x*g % p;
		j = x % 3;
		triangle T(t[j],t[(j+1)%3],t[(j+2)%3]);
		fprintf(stderr, "Testing area of [%lu,%lu,%lu]...\n",
				T.s1,T.s2,T.s3);
		cout << T.area() << "\n@";
	}
	triangle t11(3,4,5);
	triangle t12(30,40,50);
	triangle t21(4,5,3);
	triangle t22(3,40,50);
	triangle t31(24,45,51);
	triangle t32(25,60,65);
	// now test similarity / congruence
	congruentTest(t11,t11);
	congruentTest(t11,t12);
	cout << "\n@";
	congruentTest(t11,t21);
	congruentTest(t11,t22);
	cout << "\n@";
	similarTest(t11,t11);
	similarTest(t11,t12);
	cout << "\n@";
	similarTest(t11,t21);
	similarTest(t11,t22);
	cout << "\n@";
	similarTest(t31,t32);
	similarTest(t32,t31);
	cout << "\n@@@";
	return 0;
}

