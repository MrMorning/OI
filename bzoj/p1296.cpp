#include <cstdio>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N_MAX = 51;
const int T_MAX = 2501;
int f[N_MAX][T_MAX];
int g[N_MAX][N_MAX][N_MAX];
int w[N_MAX][N_MAX], sum[N_MAX][N_MAX];
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n, m, t;
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 1; i <= n; i ++)
	{
		static char str[N_MAX];
		scanf("%s", str);
		for(int j = 1; j <= m; j ++)
			w[i][j] = str[j - 1] - '0';
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			sum[i][j] = sum[i][j - 1] + w[i][j];
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= m; k ++)
				for(int t = 0; t < j; t ++)
				{
					int tmp = g[i][t][k - 1] + MAX(sum[i][j] - sum[i][t], j - t - (sum[i][j] - sum[i][t]));
					g[i][j][k] = MAX(g[i][j][k], tmp);
				}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= t; j ++)
			for(int k = 0; k <= m; k ++)
				if(j - k >= 0)
					f[i][j] = MAX(f[i][j], f[i - 1][j - k] + g[i][m][k]);
	printf("%d\n", f[n][t]);
}
