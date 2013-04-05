#include <cstdio>
int n, a[1010], b[1010];
int ans;
void dfs(int i)
{
	if(i == n + 1)
	{
		if(a[i - 1] + a[i - 2] == b[i - 1])
			ans ++;
		return;
	}
	for(int t = 0; t < 2; t ++)
	{
		a[i] = t;
		if(i == 1 || (a[i] + a[i - 1] + a[i - 2] == b[i - 1]))
			dfs(i + 1);
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &b[i]);
	dfs(1);
	printf("%d\n", ans);
}
