#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;

struct Number {
	ll val;
	int nDig, dig[18];
	void refresh() {
		memset(dig, 0, sizeof(dig));
		nDig = 0;
		ll tmp = val;
		while ( tmp ) {
			dig[nDig ++] = tmp % 10;
			tmp /= 10;
		}
	}
} high;

struct Memo {
	ll ans, cnt;
};
struct F {
	Memo ele[300];
	Memo &operator[] (int x) {
		return ele[150 + x];
	}
} dpMemo[18][18][2];

struct D {
	bool ele[300];
	bool &operator[] (int x) {
		return ele[150 + x];
	}
} dpDone[18][18][2];

Memo dp(int i, int j, int hs, int delta) {
	if ( dpDone[i][j][hs][delta] )
		return dpMemo[i][j][hs][delta];
	dpDone[i][j][hs][delta] = true;
	Memo &res = dpMemo[i][j][hs][delta];
	res.ans = res.cnt = 0;

	if ( i == 0 ) {
		res.ans = delta;
		res.cnt = j;
		return res;
	}

	int lim = hs ? high.dig[i - 1] : 9;
	int odd = 1;

	for ( int x = 0; x <= lim; x ++ ) {
		int nj = j == 0 ? x != 0 : j + 1;
		Memo tmp = dp(i - 1, nj, hs && x == lim, delta + x * (nj & 1 ? 1 : -1));
		res.cnt += tmp.cnt;
		if ( odd )
			res.ans += tmp.ans;
		else
			res.ans -= tmp.ans;
		if ( tmp.cnt & 1 )
			odd ^= 1;
	}

	return res;
}

int main() {
	freopen("t.in", "r", stdin);

	while ( 1 ) {
		ll x;
		cin >> x;
		if ( x == 0 )
			break;
		high.val = x;
		high.refresh();

		memset(dpDone, 0, sizeof(dpDone));
		cout << dp(high.nDig, 0, 1, 0).ans << '\n';
	}
}
