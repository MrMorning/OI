#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 1000010;
const int MOD = 1162789;
int n, m;
ll h[N_MAX], g[N_MAX], p[N_MAX];
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	p[0] = 1;
	for ( int i = 1; i < n; i ++ )
		p[i] = p[i - 1] * MOD;
	for ( int i = 0; i < m; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		u --, v --;
		h[u] += p[v];
		h[v] += p[u];
	}
	for ( int i = 0; i < n; i ++ )
		g[i] = h[i] + p[i];
	ll ans = 0;

	sort(h, h + n);
	for ( int i = 0; i < n; i ++ ) {
		int j = i;
		while ( i + 1 < n && h[i] == h[i + 1] ) i ++;
		ans += (ll)(i - j + 1) * (i - j) / 2;
	}
	sort(g, g + n);
	for ( int i = 0; i < n; i ++ ) {
		int j = i;
		while ( i + 1 < n && g[i] == g[i + 1] ) i ++;
		ans += (ll)(i - j + 1) * (i - j) / 2;
	}

	cout << ans << '\n';
}
