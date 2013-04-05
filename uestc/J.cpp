#include <cstdio>
typedef long long ll;
const int N_MAX = 100010;
const int MOD = 1000003;
int n, m;
int sa[N_MAX], rank[N_MAX];
int f[N_MAX], g[N_MAX], sum[N_MAX];

int pow_mod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = (ll)a * a % MOD;
		if ( n & 1 )
			res = (ll)res * a % MOD;
	}
	return res;
}

int main() {
	int TST;
	scanf("%d", &TST);
	for ( int tst = 1; tst <= TST; tst ++ ) {
		scanf("%d%d", &n, &m);
		for ( int i = 1; i <= n; i ++ )
			scanf("%d", &sa[i]);
		for ( int i = 1; i <= n; i ++ ) 
			rank[sa[i]] = i;
		rank[n + 1] = 0;
		int cnt = 0;
		for ( int i = 2; i <= n; i ++ )
			if ( rank[sa[i - 1] + 1] < rank[sa[i] + 1] ) 
				cnt ++;
		for ( int i = 0; i < n - 1 - cnt; i ++ )
			f[i] = 0;
		f[n - 1 - cnt] = 1;
		for ( int i = n - cnt; i < m; i ++ )
			f[i] = (ll)f[i - 1] * i % MOD * pow_mod(i - (n - 1 - cnt), MOD - 2) % MOD;
		g[0] = 1;
		for ( int i = 1; i < m; i ++ )
			g[i] = (ll)g[i - 1] * (cnt + i - 1) % MOD * pow_mod(i, MOD - 2) % MOD;
		sum[0] = g[0];
		for ( int i = 1; i < m; i ++ )
			sum[i] = (sum[i - 1] + g[i]) % MOD;
		int res = 0;
		for ( int i = 0; i < m; i ++ ) {
			res += (ll)f[i] * sum[m - i - 1] % MOD;
			res %= MOD;
		}
		printf("Case #%d: %d\n", tst, res);
	}
}
