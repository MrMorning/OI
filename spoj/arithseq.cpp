#include <cstdio>
#include <iostream>
#define CEIL_DIV(a, b) ((a) % (b) == 0 ? (a) / (b) : (a) / (b) + 1)
using namespace std;
typedef long long ll;
int A, D, N, X;
bool dpDone[18][2][2][2][20000];
struct Memo {
	ll ans, cnt;
} dpMemo[18][2][2][2][20000];

struct Number {
	ll val;
	int nDig, dig[18];
	void refresh() {
		nDig = 0;
		ll tmp = val;
		while ( tmp ) {
			dig[nDig ++] = tmp % 10;
			tmp /= 10;
		}
	}
} low, high;

Memo dp(int n, int ls, int hs, int zero, int p) {
	if ( dpDone[n][ls][hs][zero][p] )
		return dpMemo[n][ls][hs][zero][p];
	dpDone[n][ls][hs][zero][p] = true;
	Memo &res = dpMemo[n][ls][hs][zero][p];
	res.ans = res.cnt = 0;
	if ( n == 0 ) {
		res.cnt = (p == A % D);
		res.ans = 0;
		return res;
	}
	int lb = ls ? low.dig[n - 1] : 0,
		hb = hs ? high.dig[n - 1] : 9;
	for ( int x = lb; x <= hb; x ++ ) {
		Memo tmp = dp(n - 1, ls && x == lb, hs && x == hb, zero && x == 0, (p * 10 + x) % D);
		res.cnt += tmp.cnt;
		res.ans += tmp.ans;
		if ( x == X && !(X == 0 && zero) )
			res.ans += tmp.cnt;
	}
	return res;
}

int main() {
	cin >> A >> D >> N >> X;

	low.val = A;
	high.val = A + (ll)D * N;
	low.refresh();
	high.refresh();
	cout << dp(high.nDig, 1, 1, 1, 0).ans;
}
