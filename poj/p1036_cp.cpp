#include <cstdio>
#include <cstring>
#define MAXN 101

int n, m, T;
int time[MAXN], p[MAXN], s[MAXN];
int f[30001][101], w[30001][101];

inline int max(int a, int b)
{return a > b ? a: b; }

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d\n", &n, &m, &T);
	for(int i = 1; i <= n; i ++)
		scanf("%d\n", &time[i]);
	for(int i = 1; i <= n; i ++)
		scanf("%d\n", &p[i]);
	for(int i = 1; i <= n; i ++)
		scanf("%d\n", &s[i]);
	for(int i = 1; i <= n; i ++)
		w[time[i]][s[i]] += p[i];
	for(int i = 1; i <= T; i ++)
		for(int j = 0; j <= m; j ++)
		{
			f[i][j] = f[i - 1][j] + w[i - 1][j];
			if(j > 0)
				f[i][j] = max(f[i][j], f[i - 1][j - 1] + w[i - 1][j - 1]);
			if(j < m)
				f[i][j] = max(f[i][j], f[i - 1][j + 1] + w[i - 1][j + 1]);
		}
	int ans = 0;
	for(int j = 0; j <= m; j ++)
		ans = max(ans, f[T][j]);
	printf("%d\n", ans);
}
