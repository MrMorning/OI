#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int x[1000], f[1000][128], g[1000][128];
int mat[128][128];
int n, m, s;
int ans[1000], ansCnt;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &x[i]);
	scanf("%d%d", &m, &s);
	for(int i = 0; i < m; i ++)
		for(int j = 0; j < s; j ++)
			scanf("%d", &mat[i][j]);
	memset(f, 0x3f, sizeof(f));
	for(int j = 0; j < s; j ++)
	{
		f[0][j] = abs(mat[0][j] - x[0]);
		g[0][j] = -1;
	}
	for(int i = 0; i < n - 1; i ++)
		for(int j = 0; j < s; j ++)
		{
			int t = j % m;
			for(int k = 0; k < s; k ++)
			{
				int val = f[i][j] + abs(x[i + 1] - mat[t][k]);
				if(val < f[i + 1][k])
				{
					f[i + 1][k] = val;
					g[i + 1][k] = j;
				}
			}
		}
	int t = -1;
	for(int j = 0; j < s; j ++)
		if(t == -1 || f[n - 1][t] > f[n - 1][j])
			t = j;
	printf("%d\n", f[n - 1][t]);
	ans[ansCnt ++] = t;
	for(int i = n - 1; i > 0; t = g[i][t], i --)
		ans[ansCnt ++] = g[i][t];
	for(int i = ansCnt - 1; i >= 0; i --)
		printf("%d ", ans[i]);
}
