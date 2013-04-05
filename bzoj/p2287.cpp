#include <cstdio>
#include <cstring>
const int N_MAX = 2010;
int f[N_MAX], g[N_MAX], w[N_MAX];
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &w[i]);
	f[0] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = m; j >= w[i]; j --)
			f[j] = (f[j] + f[j - w[i]]) % 10;
	for(int i = 1; i <= n; i ++)
	{
		memset(g, 0, sizeof(g));
		g[0] = 1;
		for(int j = 1; j <= m; j ++)
			if(j - w[i] < 0)
				g[j] = f[j];
			else
				g[j] = (f[j] - g[j - w[i]] + 10) % 10;
		for(int j = 1; j <= m; j ++)
			printf("%d", g[j]);
		printf("\n");
	}
}
