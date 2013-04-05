#include <cstdio>
#include <cmath>
#include <cassert>
#include <iostream>
using namespace std;
typedef long long ll;
ll out[555];
int nOut = 0;
ll findLeastDivisor(ll n) {
	for ( ll x = 2, lim = (ll)sqrt(n); x <= lim; x ++ ) 
		if ( n % x == 0 ) 
			return x;
	return -1;
}

void solve(ll a, ll b) {
	assert(a % 2 == 0 && b % 2 == 0);
	while ( a != b ) {
		int t;
		for ( t = -1; !(a & (1LL << (t + 1))); t ++ );
		if ( a == (1LL << (t + 1)) )
			t --;
		assert(t != -1);
		for ( int k = t; k >= 0; k -- )
			if ( a + (1LL << (k+1)) <= b ) {
				a += 1LL << (k+1);
				out[nOut++] = a;
				break;
			}
	}
}

int main() {
	ll a, b;
	cin >> a >> b;
	ll pa = findLeastDivisor(a),
	   pb = findLeastDivisor(b);
	if ( pa == -1 || pb == -1 ) {
		cout << "Impossible\n";
		return 0;
	}
	out[nOut++] = a;
	if ( pa != 2 ) {
		a = a + pa;
		out[nOut++] = a;
	}
	bool flag = false;
	if ( pb != 2 ) {
		b = b - pb;
		flag = true;
	}
	if ( a > b ) {
		cout << "Impossible\n";
		return 0;
	}
	solve(a, b);
	if ( flag )
		out[nOut++] = b + pb;
	for ( int i = 0; i < nOut; i ++ )
		cout << out[i] << '\n';
}
