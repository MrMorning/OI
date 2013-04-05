#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 182;
int n, m;
int board[N_MAX][N_MAX], sum[N_MAX][N_MAX];
int f[2][N_MAX][N_MAX], fMax[2][N_MAX][N_MAX];
int g[2][N_MAX][N_MAX], gMax[2][N_MAX][N_MAX];
int h[2][N_MAX][N_MAX];

int fMaxInfo[2][N_MAX][N_MAX], gMaxInfo[2][N_MAX][N_MAX];
int gInfo[2][N_MAX][N_MAX][2];
int hInfo[2][N_MAX][N_MAX][4];

int res, resI, resJ, resK, resInfo[4];

bool noObstacle(int i, int j, int k)
{
	return sum[i][k] - sum[i][j - 1] == 0;
}

void paint(int x1, int y1, int x2, int y2)
{
	for(int i = x1; i <= x2; i ++)
		for(int j = y1; j <= y2; j ++)
			board[i][j] = 8;
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
	for(int i = 1; i <= n; i ++)
	{
		memset(f[i & 1], 0, sizeof(f[i & 1]));
		memset(g[i & 1], 0, sizeof(g[i & 1]));
		memset(fMax[i & 1], 0, sizeof(fMax[i & 1]));
		memset(gMax[i & 1], 0, sizeof(gMax[i & 1]));
		memset(h[i & 1], 0, sizeof(h[i & 1]));
		for(int j = 1; j <= m; j ++)
		{
			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
					f[i & 1][j][k] = f[(i - 1) & 1][j][k] + k;

			for(int k = m - j + 1; k >= 1; k --)
			{
				fMax[i & 1][j][k] = fMax[i & 1][j][k + 1];
				fMaxInfo[i & 1][j][k] = fMaxInfo[i & 1][j][k + 1];
				if(f[i & 1][j][k + 1] > fMax[i & 1][j][k])
				{
					fMax[i & 1][j][k] = f[i & 1][j][k + 1];
					fMaxInfo[i & 1][j][k] = k + 1;
				}
			}

			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
				{
					if(g[(i - 1) & 1][j][k] > 0)
					{
						g[i & 1][j][k] = g[(i - 1) & 1][j][k] + k;
						gInfo[i & 1][j][k][0] = gInfo[(i - 1) & 1][j][k][0];
						gInfo[i & 1][j][k][1] = gInfo[(i - 1) & 1][j][k][1] + 1;

					}
					if(fMax[(i - 1) & 1][j][k] > 0 && fMax[(i - 1) & 1][j][k] + k > g[i & 1][j][k])
					{
						g[i & 1][j][k] = fMax[(i - 1) & 1][j][k] + k;
						gInfo[i & 1][j][k][0] = fMax[(i - 1) & 1][j][k] / fMaxInfo[(i - 1) & 1][j][k];
						gInfo[i & 1][j][k][1] = 1;
					}
				}

			for(int k = 1; k <= m - j + 1; k ++)
			{
				gMax[i & 1][j][k] = gMax[i & 1][j][k - 1];
				gMaxInfo[i & 1][j][k] = gMaxInfo[i & 1][j][k - 1];
				if(g[i & 1][j][k - 1] > gMax[i & 1][j][k])
				{
					gMax[i & 1][j][k] = g[i & 1][j][k - 1];
					gMaxInfo[i & 1][j][k] = k - 1;
				}
			}

			for(int k = 1; k <= m - j + 1; k ++)
				if(noObstacle(i, j, j + k - 1))
				{
					if(h[(i - 1) & 1][j][k] > 0)
					{
						h[i & 1][j][k] = h[(i - 1) & 1][j][k] + k;
						for(int t = 0; t < 4; t ++)
							hInfo[i & 1][j][k][t] = hInfo[(i - 1) & 1][j][k][t];
					}
					if(gMax[(i - 1) & 1][j][k] > 0 && gMax[(i - 1) & 1][j][k] + k > h[i & 1][j][k])
					{
						h[i & 1][j][k] = gMax[(i - 1) & 1][j][k] + k;
						int t = gMaxInfo[(i - 1) & 1][j][k];
						hInfo[i & 1][j][k][0] = gInfo[(i - 1) & 1][j][t][0];
						hInfo[i & 1][j][k][1] = (g[(i - 1) & 1][j][t] - t * gInfo[(i - 1) & 1][j][t][1]) / gInfo[(i - 1) & 1][j][t][0];
						hInfo[i & 1][j][k][2] = gInfo[(i - 1) & 1][j][t][1];
						hInfo[i & 1][j][k][3] = t;
					}
					if(h[i & 1][j][k] > res)
					{
						res = h[i & 1][j][k];
						memcpy(resInfo, hInfo[i & 1][j][k], sizeof(resInfo));
						resI = i, resJ = j, resK = k;
					}
				}
		}
	}

	if(res == 0)
		printf("-1\n");
	else
	{
		printf("%d\n", res);
		int a = resInfo[0], b = resInfo[1], c = resInfo[2], d = resInfo[3];
		int e = (res - a * b - c * d) / resK, f = resK;
		paint(resI - a - c - e + 1, resJ, resI - c - e, resJ + b - 1);
		paint(resI - c - e + 1, resJ, resI - e, resJ + d - 1);
		paint(resI - e + 1, resJ, resI, resJ + f - 1);
		for(int i = 1; i <= n; i ++, printf("\n"))
			for(int j = 1; j <= m; j ++)
				printf("%d ", board[i][j]);
	}
}
