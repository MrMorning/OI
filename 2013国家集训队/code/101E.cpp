#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
using namespace std;
typedef long long ll;
const int kNMax = 20005;
int x[kNMax], y[kNMax], p, n, m;
pair<int, int> ans[kNMax*2];

inline int eval(int i, int j) {
	return (x[i]+y[j])%p;
}

void solve(int x1, int y1, int x2, int y2) {
	static ll f[2][kNMax];
	static ll mem[kNMax];
	int lim = (x1+y1+x2+y2)/2;
	if ( lim == x1+y1 || lim == x2+y2 ) return;

	f[0][x1] = eval(x1, y1);
	int cur = 0;
	for ( int i = x1+y1+1; i <= lim; i ++, cur^=1 ) {
		int l = max(x1, i-y2), r = min(x2, i-y1);
		for ( int j = l; j <= r; j ++ ) 
			f[!cur][j] = max(i-1-j>=y1?f[cur][j]:0, j>x1?f[cur][j-1]:0) + eval(j, i-j);
	}
	for ( int i = x1; i <= x2; i ++ ) {
		int j = lim-i;
		if ( y1 <= j && j <= y2 ) 
			mem[i] = f[cur][i];
	}
	
	f[0][x2] = eval(x2, y2);
	cur = 0;
	for ( int i = x2+y2-1; i >= lim; i--, cur^=1 ) {
		for ( int j = max(x1, i-y2); j <= min(x2, i-y1); j ++ ) 
			f[!cur][j] = max(i+1-j<=y2?f[cur][j]:0, j<x2?f[cur][j+1]:0) + eval(j, i-j);
	}
	ll best = -1;
   	int bestX;
	for ( int i = x1; i <= x2; i ++ ) {
		int j = lim-i;
		if ( y1 <= j && j <= y2 ) {
			ll tmp = mem[i]+f[cur][i]-eval(i,j);
			if ( tmp > best ) {
				best = tmp;
				bestX = i;
			}
		}
	}
	ans[lim] = make_pair(bestX, lim-bestX);
	solve(x1, y1, bestX, lim-bestX);
	solve(bestX, lim-bestX, x2, y2);
}

ll brute() {
	static ll f[2][kNMax];
	memset(f, 0, sizeof(f));
	int x1 = 0, y1 = 0, x2 = n-1, y2 = m-1;
	f[0][x1] = eval(x1, y1);
	int cur = 0;
	ll res = 0;
	for ( int i = x1+y1+1; i <= n+m-2; i ++, cur^=1 ) {
		memset(f[!cur], 0, sizeof(f[!cur]));
		for ( int j = max(x1, i-y2); j <= min(x2, i-y1); j ++ ) {
			f[!cur][j] = max(f[cur][j], j>x1?f[cur][j-1]:0) + eval(j, i-j);
			if ( i == n+m-2 )
				res = max(res, f[!cur][j]);
		}
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &p);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &x[i]);
	for ( int i = 0; i < m; i ++ )
		scanf("%d", &y[i]);
	ans[0] = make_pair(0, 0);
	ans[n+m-2] = make_pair(n-1, m-1);
	solve(0, 0, n-1, m-1);

	ll tot = 0;
	for ( int i = 0; i <= n+m-2; i ++ )
		tot += eval(ans[i].first, ans[i].second);
	//assert(tot == brute());
	printf(LL_FMT "\n", tot);
	for ( int i = 1; i <= n+m-2; i ++ )
		if ( ans[i].first == ans[i-1].first )
			putchar('S');
		else {
			assert(ans[i].second == ans[i-1].second);
			putchar('C');
		}
}
