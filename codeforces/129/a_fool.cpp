#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
typedef long long ll;

int len(ll a) {
	int ret = 0;
	while ( a ) {
		ret ++;
		a /= 10;
	}
	return ret;
}

int first(ll a) {
	vector<int> res;
	while ( a ) {
		res.push_back(a%10);
		a/=10;
	}
	return res.back();
}

ll solve(ll x) {
	if ( x == 0 )
		return 0;
	ll ans = min(9ll, x);
	if ( first(x) > x % 10 ) 
		ans--;
	return x / 10 + ans;
}

int main() {
	freopen("t.in", "r", stdin);
	ll l, r;
	cin >> l >> r;
	cout << solve(r) - solve(l-1) << endl;
}
