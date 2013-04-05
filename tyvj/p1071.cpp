#include <cstdio>
#define MAXN 3001

int n, a[MAXN], b[MAXN], f[MAXN][MAXN];

inline int max(int a, int b)
{
	return a > b ? a: b;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &b[i]);
	for(int i = 1; i <= n; i ++)
	{
		int k = 0;
		for(int j = 1; j <= n; j ++)
		{
			f[i][j] = f[i - 1][j];
			if(a[i] == b[j] && f[i][k] + 1 > f[i][j])
				f[i][j] = f[i - 1][k] + 1;
			else if(a[i] > b[j] && f[i - 1][k] < f[i-1][j])
				k = j;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans = max(ans, f[n][i]);
	printf("%d\n", ans);
}
