#include <cstdio>
#include <cstdlib>
typedef long long ll;
int MOD, A, n;
int f[1111][555];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &A, &n, &MOD);
	f[0][0] = 1;
	for ( int i = 1; i <= A; i ++ )
		for ( int j = 0; j <= n; j ++ )
			f[i][j] = (f[i - 1][j] + (j ? i * f[i - 1][j - 1] % MOD: 0)) % MOD;
	int res = f[A][n];
	for ( int i = 1; i <= n; i ++ )
		res = (ll)res * i % MOD;
	printf("%d\n", res);
}
