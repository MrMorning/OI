#include <cstdio>
#include <cstring>
#include <queue>
#include <cassert>
#define INF 0x3f3f3f3f
#define MAXN 510
using std::queue;

int c[MAXN][MAXN], flow[MAXN], prev[MAXN], n, n1, n2, sink, src;
bool vis[MAXN];

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int findArg()
{
	queue<int> q;
	q.push(src);
	memset(prev, 0, sizeof(prev));
	memset(vis, 0, sizeof(vis));
	flow[src] = INF;
	vis[src] = true;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == sink)
			return flow[u];
		for(int v = 1; v <= n; v ++)
			if(! vis[v] && c[u][v])
			{
				vis[v] = true;
				flow[v] = min(flow[u], c[u][v]);
				q.push(v);
				prev[v] = u;
			}
	}
	return 0;
}

inline int point2idx(int i, int j)
{
	int ret =  (i - 1) * n1 + j;
	assert(ret <= n);
	return ret;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n1, &n2);
	n = n1 * n2 + n1 + 2, src = n - 1, sink = src + 1;
	for(int i = 1, t; i <= n2; i ++)
	{
		scanf("%d", &t);
		c[src][point2idx(i + 1, 1)] = t;
	}
	for(int i = 1, t, m; i <= n1; i ++)
	{
		scanf("%d", &t);
		c[point2idx(1, i)][sink] = t;
		scanf("%d", &m);
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &t);
			c[point2idx(t + 1, i)][point2idx(1, i)] = INF;
		}
		scanf("%d", &m);
		static int tmp[MAXN];
		for(int j = 1; j <= m; j ++)
			scanf("%d", &tmp[j]);
		if(i < n1)
			for(int j = 1; j <= m; j ++)
				for(int k = 1; k <= m; k ++)
					c[point2idx(tmp[j] + 1, i)][point2idx(tmp[k] + 1, i + 1)] = INF;
	}
	for(int i = 2; i <= n2 + 1; i ++)
		for(int j = 1; j < n1; j ++)
			c[point2idx(i, j)][point2idx(i, j + 1)] = INF;
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
	printf("%d\n", ans);
}
