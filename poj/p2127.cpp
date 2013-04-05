#include <cstdio>
#include <cstring>
#define MAXN 510

int n, m, a[MAXN], b[MAXN], f[MAXN][MAXN];
int g[MAXN][MAXN], prev = 0x3f3f3f3f;
int ans[MAXN], ansNum = 0;

inline int max(int a, int b)
{
	return a > b ? a: b;
}

void print(int i, int j)
{
	if(g[i][j])
		print(i - 1, g[i][j]);
	if(b[j] != prev)
		ans[++ ansNum] = b[j];
	prev = b[j];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	scanf("%d\n", &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d", &b[i]);
	for(int i = 1; i <= n; i ++)
	{
		int k = 0;
		for(int j = 1; j <= m; j ++)
		{
			f[i][j] = f[i - 1][j];
			g[i][j] = j;
			if(a[i] == b[j] && f[i][k] + 1 > f[i][j])
				f[i][j] = f[i - 1][k] + 1, g[i][j] = k;
			else if(a[i] > b[j] && f[i - 1][k] < f[i-1][j])
				k = j;
		}
	}
	memset(ans, 0, sizeof(ans));
	int ans_j = ansNum = 0;
	for(int i = 1; i <= m; i ++)
	{
		if(f[n][i] > ans[0])
		{
			ans[0] = f[n][i];
			ans_j = i;
		}
	}
	printf("%d\n", ans[0]);
	print(n, ans_j);
	for(int i = 1; i < ansNum; i ++)
		printf("%d ", ans[i]);
	printf("%d\n", ans[ansNum]);
}
