#include <cstdio>
#include <cstring>
typedef long long ll;

int MOD;
int f[33][555], g[33][555], f_now[555], f_nxt[555];

int pow_mod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = (ll)a * a % MOD;
		if ( n & 1 )
			res = (ll)res * a % MOD; 
	}
	return res;
}
/*
int bino(int k, int n) {
	//choose n elements from 2^k
	int res = 1;
	for ( int i = 1; i <= (1 << k); i ++ )
		res = (ll)res * i % MOD;
	for ( int i = 1; i <= (1 << k) - n; i ++ )
		res = (ll)res * pow_mod(i, MOD - 2) % MOD;
	for ( int i = 1; i <= n; i ++ )
		res = (ll)res * pow_mod(i, MOD - 2) % MOD;
	return res;
}*/

int bino(int n, int k) {
	int res = 1;
	for ( int i = 1; i <= n; i ++ )
		res = (ll)res * i % MOD;
	for ( int i = 1; i <= n - k; i ++ )
		res = (ll)res * pow_mod(i, MOD - 2) % MOD;
	for ( int i = 1; i <= k; i ++ )
		res = (ll)res * pow_mod(i, MOD - 2) % MOD;
	return res;
}

int extend(int L, int n, int k) {
	if ( n > (1 << k) )
		return 0;
	int res = 0;
	for ( int t = 0; t <= n; t ++ ) 
		res = (res + (ll)pow_mod(L, n - t) * f[k][t] % MOD * bino((1 << k) - t, n - t)) % MOD;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int A, n;
	
	scanf("%d%d%d", &A, &n, &MOD);

	f[0][0] = f[0][1] = 1;
	for ( int j = 0; j <= n; j ++ ) 
		g[0][j] = extend(1 << 0, j, 0) % MOD;
	int lim = 0;
	while ( (1 << (lim + 1)) <= A )
		lim ++;
	for ( int i = 1; i <= lim; i ++ ) 
		for ( int j = 0; j <= n; j ++ ) {
			for ( int p = 0; p <= j; p ++ ) {
				f[i][j] = (f[i][j] + (ll)f[i - 1][p] * g[i - 1][j - p] % MOD) % MOD;
			}
			g[i][j] = extend(1 << i, j, i) % MOD;
		}

	memcpy(f_now, f[lim], sizeof(f[lim]));
	int L = 1 << lim;
	for ( int i = lim - 1; i >= 0; i -- ) 
		if ( A & (1 << i) ) {
			memset(f_nxt, 0, sizeof(f_nxt));
			for ( int j = 0; j <= n; j ++ )
				for ( int t = 0; t <= j; t ++ ) 
					f_nxt[j] = (f_nxt[j] + (ll)f_now[j - t] * extend(L, t, i) % MOD) % MOD;
			memcpy(f_now, f_nxt, sizeof(f_nxt));
			L += 1 << i;
		}
	int res = f_now[n];
	for ( int i = 1; i <= n; i ++ )
		res = (ll)res * i % MOD;
	printf("%d\n", res);
}
