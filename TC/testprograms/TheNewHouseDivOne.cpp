#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)

using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;

class TheNewHouseDivOne {
public:
	int dist[55];
	double distance(vector <int> x, vector <int> y, int k) {
		int n = x.size();
		int minX = inf, maxX = -inf,
			minY = inf, maxY = -inf;
		for ( int i = 0; i < n; i ++ ) {
			x[i] *= 2, y[i] *= 2;
			minX = min(minX, x[i]);
			maxX = max(maxX, x[i]);
			minY = min(minY, y[i]);
			maxY = max(maxY, y[i]);
		}
		int ans = inf;
		for ( int i = minX; i <= maxX; i ++ )
			for ( int j = minY; j <= maxY; j ++ ) {
				for ( int t = 0; t < n; t ++ )
					dist[t] = abs(i - x[t]) + abs(j - y[t]);
				sort(dist, dist + n);
				ans = min(ans, dist[k-1]);
			}
		return (double)ans/2;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, int p2, bool hasAnswer, double p3) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << p2;
	cout << "]" << endl;
	TheNewHouseDivOne *obj;
	double answer;
	obj = new TheNewHouseDivOne();
	clock_t startTime = clock();
	answer = obj->distance(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p3 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = fabs(p3 - answer) <= 1e-9 * max(1.0, fabs(p3));
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	vector <int> p0;
	vector <int> p1;
	int p2;
	double p3;
	
	{
	// ----- test 0 -----
	int t0[] = {-1,-1,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1,1,-1,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 3;
	p3 = 2.0;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {-1,-1,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1,1,-1,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 2;
	p3 = 1.0;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {4,4,4,4,4,3,3,5,5};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {7,7,7,4,4,5,6,5,6};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 9;
	p3 = 1.5;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {30,-15,24,-23,43,-8,-6,-47,23,-11,43,6,-18,44,-46,16,32,31,13,9,22,25,4,-44,38,-41,-20,41,-35,7,25,39,-36,-20,-5,-38,-15,-22,0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-45,-7,-33,31,-8,-33,-20,-14,-50,-48,-31,35,-24,-31,-11,41,-41,-11,46,-1,-5,5,-39,-26,-40,-9,16,38,-30,34,46,-17,-27,33,-38,28,46,-16,-46};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 13;
	p3 = 32.0;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING

//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!