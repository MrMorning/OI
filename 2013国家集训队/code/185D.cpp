#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

ll powMod(ll a, ll n, ll p) {
	a %= p;
	ll res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = a * a % p;
		if ( n & 1 ) 
			res = res * a % p;
	}
	return res;
}

ll pow2(ll a, ll n, ll p) {
	//return a^(2^n) % p
	if ( a % p == 0 ) return 0;
	if ( p == 2 ) return a & 1;
	else {
		n = powMod(2, n, p-1);
		return powMod(a, n, p);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	int TST = 0;
	cin >> TST;
	while ( TST -- ) {
		ll k, l, r, p;
		cin >> k >> l >> r >> p;
		ll ans = 0;
		if ( k == 1 ) 
			ans = 2 % p;
		else {
			if ( pow2(k, l, p) == 1 ) {
				if ( k & 1 ) 
					ans = 2 % p;
				else
					ans = powMod(2, r+1-l, p);
			} else {
				ll up = pow2(k, r+1, p)-1;
				if ( up < 0 ) up += p;
				ll down = pow2(k, l, p)-1;
				if ( down < 0 ) down += p;
				assert(down != 0);
				down = powMod(down, p-2, p);
				ans = up * down % p;
				if ( k & 1 ) {
					assert(powMod(2,r-l,p) != 0);
					ll inv = powMod(powMod(2,r-l,p), p-2, p);
					ans = ans * inv % p;
				}
			}
		}
		cout << ans << '\n';
	}
}
