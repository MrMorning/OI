#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;
const double eps = 1e-8;

int getAns(double t) {
	if ( abs(t - round(t)) < eps ) {
		return (int)round(t);
	}
	return ceil(t);
}

int main() {
	freopen("t.in", "r", stdin);
	ll k, b, n, t;
	cin >> k >> b >> n >> t;

	if ( k == 1 ) {
		ll need = 1 + b * n;

		for ( int x = 0; x <= n; x ++ ) {
			ll cur = t + b * x;

			if ( cur >= need ) {
				cout << x << endl;
				return 0;
			}
		}
	}

	double temp = n + log(b + k - 1) / log(k) - log(k * t + b - t) / log(k);
	if ( temp < 0 ) 
		temp = 0;
	cout << getAns(temp) << endl;
	return 0;
}
