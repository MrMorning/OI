#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 182;
struct Info
{
	int a, b, c, d;
};
int n, m;
int board[N_MAX][N_MAX], sum[N_MAX][N_MAX];
int f[2][N_MAX][N_MAX], fmax[2][N_MAX][N_MAX];
int g[2][N_MAX][N_MAX], gmax[2][N_MAX][N_MAX];
int h[2][N_MAX][N_MAX];
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
			scanf("%d", &board[i][j]);
			sum[i][j] = sum[i][j - 1] + board[i][j];
		}
	int res = 0;
	for(int i = 1; i <= n; i ++)
	{
		memset(f[i & 1], 0, sizeof(f[i & 1]));
		memset(g[i & 1], 0, sizeof(g[i & 1]));
		memset(fmax[i & 1], 0, sizeof(fmax[i & 1]));
		memset(gmax[i & 1], 0, sizeof(gmax[i & 1]));
		memset(h[i & 1], 0, sizeof(h[i & 1]));
		for(int j = 1; j <= m; j ++)
		{
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
					f[i & 1][j][k] = f[(i - 1) & 1][j][k] + k;
			for(int k = m - j + 1; k >= 1; k --)
				fmax[i & 1][j][k] = max(fmax[i & 1][j][k + 1], f[i & 1][j][k + 1]);
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
				{
					if(g[(i - 1) & 1][j][k] > 0)
						g[i & 1][j][k] = max(g[i & 1][j][k], g[(i - 1) & 1][j][k] + k);
					if(fmax[(i - 1) & 1][j][k] > 0)
						g[i & 1][j][k] = max(g[i & 1][j][k], fmax[(i - 1) & 1][j][k] + k);
				}
			for(int k = 1; k <= m - j + 1; k ++)
				gmax[i & 1][j][k] = max(gmax[i & 1][j][k - 1], g[i & 1][j][k - 1]);
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
				{
					if(h[(i - 1) & 1][j][k] > 0)
						h[i & 1][j][k] = max(h[i & 1][j][k], h[(i - 1) & 1][j][k] + k);
					if(gmax[(i - 1) & 1][j][k] > 0)
						h[i & 1][j][k] = max(h[i & 1][j][k], gmax[(i - 1) & 1][j][k] + k);
					res = max(res, h[i & 1][j][k]);
				}
		}
	}

	if(res == 0)
		printf("-1\n");
	else
		printf("%d\n", res);
}
