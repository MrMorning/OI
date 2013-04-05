#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	ios::sync_with_stdio(false);
	int TST;

	cin >> TST;
	while ( TST -- ) {
		ll A, B, C, D, K;

		cin >> A >> B >> C >> D >> K;
		ll g1 = gcd(A, B), g2 = gcd(C, D),
		   k = gcd(g1, g2);
		if ( (long double)g1 * g2 / k > 1e18 )
			cout << 1 << '\n';
		else
			cout << 2 * (K / (g1 / k) / g2) + 1 << '\n';
	}
}
