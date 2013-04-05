#include <cstdio>
#include <algorithm>
using namespace std;
const int N_MAX = 2010;
int n, m, ans1, ans2;
int a[N_MAX][N_MAX], f[N_MAX][N_MAX], g[N_MAX][N_MAX][2], up[N_MAX][N_MAX], left[N_MAX][N_MAX], right[N_MAX][N_MAX];
void solve()
{
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(a[i][j])
			{
				f[i][j] = min(f[i][j - 1], min(f[i - 1][j], f[i - 1][j - 1])) + 1;
				ans1 = max(ans1, f[i][j]);
			}
			else
				f[i][j] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(a[i][j])
				up[i][j] = up[i - 1][j] + 1, left[i][j] = left[i][j - 1] + 1;
			else
				up[i][j] = 0, left[i][j] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = m; j >= 1; j --)
			right[i][j] = a[i][j] ? right[i][j + 1] + 1 : 0; 

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			if(!a[i][j])
				g[i][j][0] = g[i][j][1] = 0;
			else
			{
				g[i][j][0] = left[i][j], g[i][j][1] = right[i][j];
				if(up[i][j] > 1)
				{
					g[i][j][0] = min(g[i - 1][j][0], left[i][j]);
					g[i][j][1] = min(g[i - 1][j][1], right[i][j]);
				}
				ans2 = max(ans2, up[i][j] * (g[i][j][0] + g[i][j][1] - 1));
			}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &a[i][j]);
			if((i + j) & 1)
				a[i][j] ^= 1;
		}
	solve();
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			a[i][j] ^= 1;
	solve();
	printf("%d\n%d\n", ans1 * ans1, ans2);
}
