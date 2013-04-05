#include <cstdio>
int n, p, b, a[100], cnt[100], pre[10000];
bool vis[10000];
void dfs(int x)
{
	vis[x] = true;
	for(int i = 0; i < n; i ++)
	{
		int y = (x + a[i]) % p;
		if(!vis[y])
		{
			pre[y] = i;
			dfs(y);
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &p, &b);
	for(int i = 0, t; i < n; i ++)
	{
		scanf("%d", &t);
		a[i] = t % p;
	}
	pre[0] = -1;
	dfs(0);
	if(!vis[b])
		printf("NO\n");
	else
	{
		printf("YES\n");
		int i = b;
		while(pre[i] != -1)
			cnt[pre[i]] ++, i = (i - a[pre[i]] + p) % p;
		for(i = 0; i < n; i ++)
			printf("%d ", cnt[i]);
	}
}
