
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}

pair<int, int> stool[1111], pencil[1111];
vector<int> out[1111];
int N, K;
int n_stool, n_pencil;
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 1; i <= N; i ++ ) {
		int c, t;
		scanf("%d%d", &c, &t);
		if ( t == 1 )
			stool[++ n_stool] = make_pair(c, i);
		else
			pencil[++ n_pencil] = make_pair(c, i);
	}
	sort(stool + 1, stool + 1 + n_stool);
	ll res = 0;
	if ( K > n_stool ) {
		for ( int i = 1; i <= n_stool; i ++ ) {
			out[i].push_back(stool[i].second);
			res += stool[i].first;
		}
		for ( int i = 1; i <= K - n_stool; i ++ ) {
			out[n_stool + i].push_back(pencil[i].second);
			res += (ll)pencil[i].first * 2;
		}
		for ( int i = K - n_stool + 1; i <= n_pencil; i ++ ) {
			out[n_stool + 1].push_back(pencil[i].second);
			res += (ll)pencil[i].first * 2;
		}
	} else {
		for ( int i = 1; i <= K - 1; i ++ ) {
			out[i].push_back(stool[n_stool - i + 1].second);
			res += stool[n_stool - i + 1].first;
		}
		int smallest = 0x3f3f3f3f;
		for ( int i = K; i <= n_stool; i ++ ) {
			out[K].push_back(stool[n_stool - i + 1].second);
			res += (ll)stool[n_stool - i + 1].first * 2;
			smallest = min(smallest, stool[n_stool - i + 1].first);
		}
		for ( int i = 1; i <= n_pencil; i ++ ) {
			out[K].push_back(pencil[i].second);
			res += (ll)pencil[i].first * 2;
			smallest = min(smallest, pencil[i].first);
		}
		res -= smallest;
	}
	cout << res / 2;
	if ( res & 1 )
		cout << ".5";
	else
		cout << ".0";
	cout << '\n';
	for ( int i = 1; i <= K; i ++ ) {
		int sz = out[i].size();
		cout << sz;
		for ( int j = 0; j < sz; j ++ )
			cout << ' ' << out[i][j];
		cout << '\n';
	}
}
