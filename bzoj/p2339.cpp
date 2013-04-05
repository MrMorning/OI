#include <cstdio>
typedef long long ll;
const int MOD = 100000007;
const int M_MAX = 1000010;
int f[M_MAX];
int fac[M_MAX], bino[M_MAX];
int powMod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = (ll)a * a % MOD;
		if ( n & 1 )
			res = (ll)res * a % MOD;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	int n, m;

	scanf("%d%d", &n, &m);
	fac[1] = 1;
	for ( int i = 2; i <= m; i ++ )
		fac[i] = (ll)fac[i - 1] * i % MOD;
	bino[0] = 1;
	for ( int i = 1; i <= m; i ++ ) {
		bino[i] = (ll)bino[i - 1] * ((ll)powMod(2, n) * powMod(i, MOD - 2) % MOD - 1) % MOD;
		if ( bino[i] < 0 )
			bino[i] += MOD;
	}
	f[0] = 1;
	f[1] = 0;
	for ( int i = 2; i <= m; i ++ ) {
		f[i] = (ll)bino[i - 1] * fac[i - 1] % MOD;
		f[i] -= f[i - 1];
		if ( f[i] < 0 )
			f[i] += MOD;
		f[i] -= ((ll)f[i - 2] * (i - 1) % MOD) * (bino[1] - (i - 2)) % MOD;
		if ( f[i] < 0 )
			f[i] += MOD;
	}
	int ans = (ll)f[m] * powMod(fac[m], MOD - 2) % MOD;
	printf("%d\n", ans);
}
