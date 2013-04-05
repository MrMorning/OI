#include <cstdio>

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

void solve() {
	int n;
	scanf("%d", &n);
	int ans = 0;
	for ( int x = 1; x <= n; x ++ )
		if ( gcd(x, n) == 1 )
			ans ++;
	printf("%d\n", ans);
}

int main() {
	freopen("shuttle.in", "r", stdin);
	freopen("shuttle.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
