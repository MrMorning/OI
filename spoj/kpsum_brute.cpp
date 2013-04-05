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
} num;

int main() {
	freopen("t.in", "r", stdin);
	while ( 1 ) {
		ll x;
		cin >> x;
		if ( x == 0 )
			break;
		ll ans = 0;
		int odd = 1;
		for ( ll y = 1; y <= x; y ++ ) {
			num.val = y;
			num.refresh();
			for ( int d = 0; d < num.nDig; d ++ ) {
				ans += (odd ? 1 : -1) * num.dig[num.nDig - 1 - d];
				odd ^= 1;
			}
		}
		cout << ans << '\n';
	}
}
