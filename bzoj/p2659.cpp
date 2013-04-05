#include <cstdio>
#include <cassert>
#include <iostream>
using namespace std;

typedef long long ll;

ll floor_sum(ll n, ll a, ll b, ll c) {
	//\sum_{0 <= x < n} \floor{(ax + b) / c}

	if ( n == 0 )
		return 0;
	ll res = n * (b / c) + (n - 1) * (a / c) * n / 2;
	a %= c, b %= c;
	return res + floor_sum((a * n + b) / c, c, (a * n + b) % c, a);
}

int main() {
	ll p, q;

	cin >> p >> q;
	cout << floor_sum((p - 1) / 2 + 1, q, 0, p) + floor_sum((q - 1) / 2 + 1, p, 0, q);
}
