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
	while ( !judge(n) ) 
		n--;
	cout << n << endl;
}
