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
const ll kInf = 0x3f3f3f3f3f3f3f3fLL;

class ImportantSequence {
	ll ak[55], ab[55];
	public:
		int getCount(vector <int> B, string operators) {
			int n = (int)B.size() + 1;
			ak[0] = 1, ab[0] = 0;
			for ( int i = 0; i < n-1; i ++ ) {
				if ( operators[i] == '+' ) {
					ab[i+1] = B[i] - ab[i];
					ak[i+1] = -ak[i];
				} else {
					ab[i+1] = ab[i] - B[i];
					ak[i+1] = ak[i];
				}
			}
			ll low = 1, high = kInf;
			for ( int i = 1; i < n; i ++ ) {
				if ( ak[i] == 1 )
					low = max(low, -ab[i]+1);
				else
					high = min(high, ab[i]-1);
			}
			if ( low > high ) return 0;
			else if ( high == kInf ) return -1;
			return (int)(high - low + 1);
		}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, string p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "\"" << p1 << "\"";
	cout << "]" << endl;
	ImportantSequence *obj;
	int answer;
	obj = new ImportantSequence();
	clock_t startTime = clock();
	answer = obj->getCount(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p2;
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
	string p1;
	int p2;

	{
		// ----- test 0 -----
		int t0[] = {3,-1,7};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "+-+";
		p2 = 2;
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		int t0[] = {1};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "-";
		p2 = -1;
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		int t0[] = {1};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "+";
		p2 = 0;
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		int t0[] = {10};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "+";
		p2 = 9;
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		int t0[] = {540,2012,540,2012,540,2012,540};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = "-+-+-+-";
		p2 = 1471;
		all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
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