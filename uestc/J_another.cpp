#include <cstdio>
const int N_MAX = 100;
const int MOD = 1000003;
int n, m;
int sa[N_MAX], rank[N_MAX];
int f[N_MAX][N_MAX];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &sa[i]);
	for ( int i = 1; i <= n; i ++ ) 
		rank[sa[i]] = i;
	rank[n + 1] = 0;
	for ( int i = 1; i <= m; i ++ )
		f[1][i] = 1;
	for ( int i = 2; i <= n; i ++ ) {
		if ( rank[sa[i - 1] + 1] < rank[sa[i] + 1] )
			for ( int j = 1; j <= m; j ++ ) 
				f[i][j] = (f[i][j - 1] + f[i - 1][j]) % MOD;
		else
			for ( int j = 1; j <= m; j ++ )
				f[i][j] = (f[i][j - 1] + f[i - 1][j - 1]) % MOD;
	}
	int res = 0;
	for ( int i = 1; i <= m; i ++ )
		res = (res + f[n][i]) % MOD;
	printf("%d\n", res);
}
