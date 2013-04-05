#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
typedef long long ll;

ll POW[16];

ll num[11];
ll n_num;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll calc(ll x) {
	ll res = 0;
	for ( ll i = 0; i < n_num; i ++ )
		res += num[i] * (x / POW[i] % 10);
	return res;
}

void dfs(ll &res, ll i, ll acc) {
	if ( i == n_num ) {
		if ( acc > 0 )
			res = gcd(res, acc);
		return;
	}
	for ( ll d = -1; d <= 1; d ++ ) 
		dfs(res, i + 1, acc + num[i] * d);
}

void solve() {
	static bool vis[20];
	static char str[20];
	cin >> str;
	ll len = strlen(str);
	memset(vis, 0, sizeof(vis));
	n_num = 0;
	for ( ll i = len - 1; i >= 0; i -- ) 
		if ( !vis[i] ) {
			ll ch = str[i];
			ll cur = 0;
			for ( ll j = i; j >= 0; j -- ) {
				cur *= 10;
				if ( str[j] == ch ) {
					vis[j] = true;
					cur += 1;
				}
			}
			num[n_num ++] = cur;
		}
	ll res = 0;
	sort(num, num + n_num);

	dfs(res, 0, 0);
	assert(res != 0);

	static vector<ll> out;
	out.clear();
	for ( ll x = 1, lim = (ll)sqrt(res); x <= lim; x ++ )
		if ( res % x == 0 ) {
			out.push_back(x);
			out.push_back(res / x);
		}
	sort(out.begin(), out.end());
	out.resize(unique(out.begin(), out.end()) - out.begin());
	for ( vector<ll>::iterator it = out.begin();
			it != out.end(); it ++ )
		cout << ' ' << *it;
	cout << '\n';
}

int main() {
	freopen("t.in", "r", stdin);
	POW[0] = 1;
	for ( ll i = 1; i < 16; i ++ )
		POW[i] = POW[i - 1] * 10;
	ll TST;
	cin >> TST;
	for ( ll i = 1; i <= TST; i ++ ) {
		cout << "Case " << i << ":";
		solve();
	}
}
