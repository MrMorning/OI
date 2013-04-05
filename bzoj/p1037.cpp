#include <cstdio>
const int N_MAX = 151, K_MAX = 21;
const int MOD_NUM = 12345678;
int f[N_MAX][N_MAX][K_MAX][K_MAX];
inline void update(int &a, int x)
{
	a = (a + x) % MOD_NUM;
}
int main()
{
	freopen("t.in", "r", stdin);
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	f[0][0][0][0] = 1;
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= m; j ++)
			for(int k1 = 0; k1 <= q; k1 ++)
				for(int k2 = 0; k2 <= q; k2 ++)
				{
					if(i < n && k1 < q)
						update(f[i + 1][j][k1 + 1][k2 ? k2 - 1 : 0], f[i][j][k1][k2]);
					if(j < m && k2 < q)
						update(f[i][j + 1][k1 ? k1 - 1 : 0][k2 + 1], f[i][j][k1][k2]);
				}
	int ret = 0;
	for(int k1 = 0; k1 <= q; k1 ++)
		for(int k2 = 0; k2 <= q; k2 ++)
			ret = (ret + f[n][m][k1][k2]) % MOD_NUM;
	printf("%d\n", ret);
}
