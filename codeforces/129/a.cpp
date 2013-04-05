#include <cstdio>
#include <algorithm>
#include <iostream>
typedef long long ll;
using namespace std;

ll memo[22][2][2][10][10];
bool done[22][2][2][10][10];

struct Number {
	int nDig, dig[22];
	ll val;
	void init() {
		ll tmp = val;
		nDig = 0;
		while ( tmp ) {
			dig[nDig++] = tmp % 10;
			tmp /= 10;
		}
	}
} low, high;

ll dp(int n, int hs, int ls, int fd, int ld) {
	if ( done[n][hs][ls][fd][ld] )
		return memo[n][hs][ls][fd][ld];
	done[n][hs][ls][fd][ld] = true;
	ll &ret = memo[n][hs][ls][fd][ld];
	if ( n == 0 ) 
		return ret = fd == ld;
	int lb = ls ? low.dig[n-1] : 0,
		hb = hs ? high.dig[n-1] : 9;
	for ( int x = lb; x <= hb; x ++ ) {
		int nld = n == 1 ? x : 0,
			nfd = fd == 0 ? x : fd;
		ret += dp(n - 1, hs && x == hb, ls && x == lb, nfd, nld);
	}
	return ret;
}

int main() {
	freopen("t.in", "r", stdin);
	cin >> low.val >> high.val;
	low.init(), high.init();
	cout << dp(high.nDig, 1, 1, 0, 0);
}
