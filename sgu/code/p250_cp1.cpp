#include <cstdio>
#include <algorithm>
using namespace std;
const int N_MAX = 182;
int n, m;
int sum[N_MAX][N_MAX];
int f[N_MAX][N_MAX][N_MAX], fmax[N_MAX][N_MAX][N_MAX];
int g[N_MAX][N_MAX][N_MAX], gmax[N_MAX][N_MAX][N_MAX];
int h[N_MAX][N_MAX][N_MAX];
bool noObstacle(int i, int j, int k)
{
	return sum[i][k] - sum[i][j - 1] == 0;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			int t;
			scanf("%d", &t);
			sum[i][j] = sum[i][j - 1] + t;
		}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
					f[i][j][k] = f[i - 1][j][k] + k;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = m - j + 1; k >= 1; k --)
				fmax[i][j][k] = max(fmax[i][j][k + 1], f[i][j][k + 1]);

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
				{
					if(g[i - 1][j][k] > 0)
						g[i][j][k] = max(g[i][j][k], g[i - 1][j][k] + k);
					if(fmax[i - 1][j][k] > 0)
						g[i][j][k] = max(g[i][j][k], fmax[i - 1][j][k] + k);
				}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= m - j + 1; k ++)
				gmax[i][j][k] = max(gmax[i][j][k - 1], g[i][j][k - 1]);


	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
				{
					if(h[i - 1][j][k] > 0)
						h[i][j][k] = max(h[i][j][k], h[i - 1][j][k] + k);
					if(gmax[i - 1][j][k] > 0)
						h[i][j][k] = max(h[i][j][k], gmax[i - 1][j][k] + k);
				}

	int res = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= m - j + 1; k ++)
				res = max(res, h[i][j][k]);
	if(res == 0)
		printf("-1\n");
	else
		printf("%d\n", res);
}
