
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
#include <iomanip>
typedef long double val_t;
pair<val_t, int> ev[400010];
int n_ev;
val_t res[100010];
ll n, a[100010], v1, v2, L;

int main(){
//	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n >> L >> v1 >> v2;
	int n_ = n;
	val_t W = (val_t)L / (v1 + v2) * v2;
	for ( int i = 0; i < n; i ++ ) 
		cin >> a[i];
	for ( int i = 0; i < n; i ++ )
		if ( a[i] <= L )
			a[n ++] = a[i] + 2 * L;
	for ( int i = 0; i < n; i ++ ) {
		ev[n_ev ++] = make_pair(a[i], 1);
		ev[n_ev ++] = make_pair(a[i] + W, -1);
	}
	sort(ev, ev + n_ev);
	val_t prev = W;
	int cnt = 0;
	int st = 0;
	while ( st < n && ev[st].first < W ) {
		cnt += ev[st].second;
		st ++;
	}
	for ( int i = st; i < n_ev; i ++ ) {
		if ( ev[i].first > 2 * L + W )
			break;
		res[cnt] += ev[i].first - prev;
		prev = ev[i].first;
		cnt += ev[i].second;
	}
	res[cnt] += 2 * L + W - prev;
	for ( int i = 0; i <= n_; i ++ )
		cout << fixed << setprecision(18) << res[i] / (2 * L) << '\n';
}
