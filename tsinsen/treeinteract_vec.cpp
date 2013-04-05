#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
using namespace std;

map<pair<int, int>, int> memo;

int size() {
	printf("size=\n");
	int n;
	scanf("%d", &n);
	return n;
}
int type() {}
int question(int p, int q) {
	printf("%d,%d?", p, q);
	int t;
	scanf("%d", &t);
	return t;
}
void submit(int x) {
	printf("submit %d\n", x);
}

bool myCmp(int i, int j) {
	return question(i, j) == 1;
}

void solve(const vector<int> &T) {
	int sz = T.size(),
		p = T[rand() % sz];
	if ( sz == 1 ) {
		submit(p);
		return;
	}
	vector<int> res(sz), path, subT;
	vector<pair<int, int> > aside;
	path.pb(p);
	subT.pb(p);
	for ( int i = 0; i < sz; i ++ ) {
		int x = T[i];
		if ( x == p ) continue;
		res[i] = question(x, p);
		if ( res[i] == 1 )
			path.pb(x);
		else if ( res[i] == -1 )
			subT.pb(x);
	}
	stable_sort(path.begin(), path.end(), myCmp);
	for ( int i = 0; i < (int)path.size()-1; i ++ )
		submit(path[i]);

	for ( int i = 0; i < sz; i ++ ) {
		int x = T[i];
		if ( x == p ) continue;
		if ( res[i] == 0 ) {
			int lb = 0, rb = (int)path.size()-1;
			while ( lb < rb - 1 ) {
				int mid = (lb + rb) / 2;
				if ( question(path[mid], x) == 1 )
					lb = mid;
				else
					rb = mid;
			}
			aside.pb(mp(lb,x));
		}
	}
	stable_sort(aside.begin(), aside.end());
	for ( int i = 0, n = aside.size(); i < n; i ++ ) {
		vector<int> anotherT;
		anotherT.pb(aside[i].second);
		while ( i+1 < n && aside[i+1].first == aside[i].first ) {
			i++;
			anotherT.pb(aside[i].second);
		}
		solve(anotherT);
	}
	solve(subT);
}

int main() {
	srand(42);
	int n = size();
	vector<int> T(n);
	for ( int i = 0; i < n; i ++ )
		T[i] = i+1;
/*	if ( type() == 1 ) {
		stable_sort(T.begin(), T.end(), myCmp);
		for ( int i = 0; i < n; i ++ )
			submit(T[i]);
	} else 
*/		solve(T);
}
