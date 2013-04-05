#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;
int X, lenA, lenB;
typedef pair<pair<long long, long long>, long long> triplell;
typedef map<triplell, long long> memo_t;
memo_t memo;
long long g(const vector<int>& a) {
	long long x = 0;
	for (int i = 0; i < a.size(); ++ i) {
		x <<= 6;
		x |= a[i];
	}
	return x;
}
long long f(vector<int>& a, vector<int>& b, long long c, int d) {	
	if (d >= lenA && d >= lenB) {
		return c==0 ? 1 : 0;
	}
	triplell abc = make_pair(make_pair(g(a), g(b)), c);
	memo_t::iterator it = memo.find(abc);
	if (it != memo.end()) return it->second;
	int m = c % X;
	long long r = 0;
	if (d >= lenA) {
		if (b[m] > 0) {
			-- b[m];
			r += f(a, b, c / X, d+1);
			++ b[m];
		}
	} else if (d >= lenB) {
		if (a[m] > 0) {
			-- a[m];
			r += f(a, b, c / X, d+1);
			++ a[m];
		}
	} else {
		for (int i = 0; i < X; ++ i) {
			int j = (m - i + X) % X;
			if (i+j <= c && a[i] > 0 && b[j] > 0) {
				-- a[i]; -- b[j];
				r += f(a, b, (c-i-j) / X, d+1);
				++ a[i]; ++ b[j];
			}
		}
	}
	memo.insert(make_pair(abc, r));
	return r;
}
int main() {
	freopen("t.in", "r", stdin);
	int T;
	cin >> T;
	for (int tt = 0; tt < T; ++ tt) {
		string A, B, C;
		cin >> X >> A >> B >> C;
		vector<int> a(X), b(X);
		lenA = A.length();
		lenB = B.length();
		for (int i = 0; i < lenA; ++ i) {
			++ a[A[i]-'0'];
		}
		for (int i = 0; i < lenB; ++ i) {
			++ b[B[i]-'0'];
		}
		long long c = strtoll(C.c_str(), 0, X);
		memo.clear();
		cout << f(a,b,c,0) << endl;
	}
}

