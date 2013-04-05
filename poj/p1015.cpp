#include <cstdio>
#include <cstring>
#define MAXN 201
#define INF 0x3f3f3f3f

int n, m, d[MAXN], p[MAXN], f[MAXN][21][912];
int g[MAXN][21][912];

inline int max(int a, int b)
{
	return a > b ? a : b;
}

inline int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	freopen("t.in", "r", stdin);
	int testNum = 0;
	while(1)
	{
		scanf("%d %d\n", &n, &m);
		if(n == 0 && m == 0)
			break;
		printf("Jury #%d\n", ++ testNum);
		for(int i = 1; i <= n; i ++)
			scanf("%d %d\n", &d[i], &p[i]);
		memset(f, 0xff, sizeof(f));
		for(int i = 0; i < MAXN; i ++)
			f[i][0][400] = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= min(i, m); j ++)
				for(int k = -400; k <= 400; k ++)
				{
					if(j <= i - 1 && f[i - 1][j][k + 400] != -1)
					{
						f[i][j][k + 400] = f[i - 1][j][k + 400];
						g[i][j][k + 400] = 1;
					}
					int t = 400 + k - (d[i] - p[i]);
					if(t >= 0 && f[i - 1][j - 1][t] != -1)
						if(f[i - 1][j - 1][t] + d[i] + p[i] > f[i][j][k + 400])
						{
							f[i][j][k + 400] = f[i - 1][j - 1][t] + d[i] + p[i];
							g[i][j][k + 400] = 2;
						}
				}
		int delta = 0;
		for(delta = 0; delta <= 400; delta ++)
		{
			if(f[n][m][400 + delta] != -1)
				break;
			if(f[n][m][400 - delta] != -1)
				break;
		}
		if(f[n][m][400 - delta] > f[n][m][400 + delta])
			delta = -delta;
		printf("Best jury has value %d for prosecution and value %d for defence:\n", (delta + f[n][m][400 + delta]) / 2, (f[n][m][400 + delta] - delta) / 2);
		int i = n, j = m, k = 400 + delta;
		int seq[MAXN], seqNum = 0;
		while(j > 0)
		{
			if(g[i][j][k] == 1)
				i --;
			else
			{
				seq[++ seqNum] = i;
				k = k - (d[i] - p[i]); 
				i --;
				j --;
			}
		}
		for(int i = seqNum; i >= 1; i --)
			printf(" %d", seq[i]);
		printf("\n");
	}
}
