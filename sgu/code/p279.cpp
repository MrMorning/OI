#include <cstdio>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#define mp(a, b) make_pair(a, b)
using namespace std;

pair<string, vector<int> > solve(vector<int> a) {
	int n = a.size();
	int p;
	for ( p = 0; p < n && a[p] > 0; p ++ );
	if ( p == n ) return mp("NO", vector<int>());

	if ( n == 1 ) {
		vector<int> res;
		res.push_back(-1);
		res.push_back(1);
		return mp("YES", res);
	}

	for ( int i = 0; i < p; i ++ ) 
		a[i]--;
	vector<bool> b(n);
	for ( int i = n-1, nZero = 0; i > p; i -- ) {
		if ( a[i] > 0 ) { 
			if ( a[i] >= nZero+1 ) {
				b[i] = true;
				a[i]--;
			} else {
				nZero++;
			}
		} else {
			nZero++;
		}
	}
	a.erase(a.begin()+p);
	pair<string, vector<int> > tmp = solve(a);
	if ( tmp.first == "NO" ) return tmp;
	vector<int> res = tmp.second;
	int m = res.size();

	for ( int i = 0; i < m; i ++ ) {
		if ( res[i] >= p+1 )
			res[i]++;
		else if ( res[i] <= -(p+1) )
			res[i]--;
	}

	int t = -1;
	for ( int i = 0; i < m; i ++ )
		if ( res[i] < 0 || (res[i] > (p+1) && b[res[i]-1]) ) {
			t = i;
		}
	res.insert(res.begin()+t+1, -(p+1));
	res.push_back(p+1);
	return mp("YES",res);
}

int main() {
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d", &a[i]);
		if ( a[i] < 0 || a[i] >= n ) {
			puts("NO");
			return 0;
		}
	}
	pair<string, vector<int> > res = solve(a);
	printf("%s\n", res.first.c_str());
	if ( res.first == "YES" ) {
		for ( int i = 0; i < 2*n; i ++ )
			printf("%d ", res.second[i]);
	}
}
