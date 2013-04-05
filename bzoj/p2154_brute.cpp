#include <cstdio>
const int MOD = 20101009;
typedef long long ll;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	ll res = 0;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			res += (ll)i * j / gcd(i, j) % MOD;
			res %= MOD;
		}
	printf("%lld\n", res);
}
