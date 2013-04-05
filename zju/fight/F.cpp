#include <iomanip>
#include <cstdio>
#include <cmath>
#include <iostream>
typedef long long ll;
typedef long double val_t;
using namespace std;
ll a, b;
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
val_t dist(ll a, ll b) {
	return sqrt(a * a + b * b);
}
val_t solve(ll a, ll b) {
	ll n = a + b - 1;
	if ( (a & 1) && (b & 1) ) {
		val_t k = (val_t)(n + 1) / (2 * n + 1);
		return dist(a, b) * k;
	} else {
		return dist(a, b) / 2;
	}
}
int main() {
	freopen("t.in", "r", stdin);
	while ( cin >> a >> b ) {
		ll k = gcd(a, b);
		a /= k, b /= k;
		val_t res = solve(a, b) * k;
		cout << setprecision(3) << setiosflags(ios::fixed) << res << '\n';
	}
}
