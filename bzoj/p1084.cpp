#include <cstdio>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int N_MAX = 101;
const int INFINITY = 32768;
int n, m, s;
int a[3][N_MAX], sum[3][N_MAX];
int f[N_MAX][N_MAX][11];
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d", &a[j][i]);
	if(m == 1)
		for(int i = 1; i <= n; i ++)
			a[2][i] = -INFINITY;
	for(int i = 1; i <= n; i ++)
	{
		sum[1][i] = sum[1][i - 1] + a[1][i];
		sum[2][i] = sum[2][i - 1] + a[2][i];
	}
	int ans = -INFINITY;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 1; k <= s; k ++)
			{
				int &tmp = f[i][j][k] = MAX(f[i - 1][j][k], f[i][j - 1][k]);
				for(int t = 0; t < i; t ++)
					tmp = MAX(tmp, f[t][j][k - 1] + sum[1][i] - sum[1][t]);
				for(int t = 0; t < j; t ++)
					tmp = MAX(tmp, f[i][t][k - 1] + sum[2][j] - sum[2][t]);
				if(i == j)
					for(int t = 0; t < i; t ++)
						tmp = MAX(tmp, f[t][t][k - 1] + sum[1][i] - sum[1][t] + sum[2][i] - sum[2][t]);
				ans = MAX(ans, tmp);
			}
	printf("%d\n", ans);
}
