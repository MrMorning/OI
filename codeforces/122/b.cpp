#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
ll a[33], b[33], k[33], p[33];
int n, u, r;
ll ans = -0x3f3f3f3f3f3f3f3fLL;
void stat() {
	ll res = 0;
	for ( int i = 1; i <= n; i ++ )
		res += (ll)k[i] * a[i];
	ans = max(ans, res);
}
void dfs(int cur, bool isXor) {
	ll bkup[33];
	if ( (u - cur + 1) % 2 == 0 )
		stat();
	if ( cur == u + 1 ) {
		return;
	}
	memcpy(bkup, a, sizeof(a));
	for ( int i = 1; i <= n; i ++ ) 
		a[i] = bkup[p[i]] + r;
	dfs(cur + 1, 0);
	memcpy(a, bkup, sizeof(a));
	if ( !isXor ) {
		for ( int i = 1; i <= n; i ++ ) 
			a[i] ^= b[i];
		dfs(cur + 1, 1);
		memcpy(a, bkup, sizeof(a));
	}
}
int main() {
	scanf("%d%d%d", &n, &u, &r);
	for ( int i = 1; i <= n; i ++ )
		cin >> a[i];
	for ( int i = 1; i <= n; i ++ )
		cin >> b[i];
	for ( int i = 1; i <= n; i ++ )
		cin >> k[i];
	for ( int i = 1; i <= n; i ++ )
		cin >> p[i];
	dfs(1, 0);
	cout << ans;
}
