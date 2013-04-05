#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

int countBits(ll x) {
	int res = 0;
	while ( x ) {
		res ++;
		x >>= 1;
	}
	return res;
}

bool judge(ll x) {
	static int a[66];
	ll ori = x;
	int n = 0;
	while ( x ) {
		a[n++] = x & 1;
		x >>= 1;
	}
	for ( int d = 0; d < n; d ++ )
		if ( a[(n-1+d)%n] ) {
			ll tmp = 0;
			for ( int i = n-1; i >= 0; i -- )
				tmp = (tmp<<1)+a[(i+d)%n];
			if ( tmp < ori ) return false;
		}
	return true;
}
int dig[66], nDig;
int main() {
	freopen("t.in", "r", stdin);
	ll n;
	cin >> n;
	if ( judge(n) ) {
		cout << n << endl;
		return 0;
	}
	ll tmp = n;
	while ( tmp ) {
		dig[nDig++] = tmp & 1;
		tmp >>= 1;
	}
	ll ans = 1LL<<(nDig-1);
	for ( int i = nDig-2; i >= 0; i-- ) 
		if ( dig[i] ) {
			ll cur = 0;
			for ( int j = nDig-1; j > i; j -- )
				cur = (cur<<1) + dig[j];
			cur <<= i+1;
			if ( judge(cur+((1LL<<i)-1)) )
				ans = max(ans, cur+((1LL<<i)-1));
		}
	cout << ans << endl;
}
