#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define MAXN 250

using std::queue;
int c[MAXN][MAXN], prev[MAXN], flow[MAXN], src, sink;
int f[MAXN][MAXN], macNum, cowNum, n, macLim;
bool vis[MAXN];

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}
int findArg()
{
	memset(vis, 0, sizeof(vis));
	memset(prev, 0, sizeof(prev));
	memset(flow, 0, sizeof(flow));
	queue<int> q;
	q.push(src);
	flow[src] = INF;
	vis[src] = true;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == sink)
			return flow[sink];
		for(int v = 1; v <= n + 2; v ++)
			if(! vis[v] && c[u][v])
			{
				vis[v] = true;
				flow[v] = min(flow[u], c[u][v]);
				prev[v] = u;
				q.push(v);
			}
	}
	return 0;
}

int maxFlow(int lim)
{
	memset(c, 0, sizeof(c));
	src = n + 1, sink = n + 2;
	for(int i = macNum + 1; i <= n; i ++)
		for(int j = 1; j <= macNum; j ++)
			if(f[i][j] <= lim)
				c[i][j] = INF;
	for(int i = macNum + 1; i <= n; i ++)
		c[src][i] = 1;
	for(int j = 1; j <= macNum; j ++)
		c[j][sink] = macLim;
	int ans = 0;
	while(int tmp = findArg())
	{
		ans += tmp;
		int v = sink;
		while(prev[v])
		{
			int u = prev[v];
			c[u][v] -= tmp;
			c[v][u] += tmp;
			v = u;
		}
	}
	return ans;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d\n", &macNum, &cowNum, &macLim);
	n = macNum + cowNum;
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
		{
			scanf("%d", &f[i][j]);
			if(f[i][j] == 0)
				f[i][j] = INF;
		}
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	int upperLim = 0;
	for(int i = macNum + 1; i <= n; i ++)
		for(int j = 1; j <= macNum; j ++)
			upperLim = max(upperLim, f[i][j]);
	int l = 0, r = upperLim, mid = (l + r) / 2;
	while(l < r)
	{
		if(maxFlow(mid) >= cowNum)
			r = mid;
		else
			l = mid + 1;
		mid = (l + r) / 2;
	}
	printf("%d\n", mid);
}
