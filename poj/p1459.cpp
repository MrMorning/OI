#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define MAXN 105
using std::queue;

int c[MAXN][MAXN], src, sink, n, np, nc, m, flow[MAXN], prev[MAXN];
bool vis[MAXN];

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int findArg()
{
	queue<int> q;
	q.push(src);
	memset(vis, 0, sizeof(vis));
	memset(prev, 0, sizeof(prev));
	vis[src] = true;
	flow[src] = INF;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == sink)
			return flow[u];
		for(int v = 1; v <= n + 2; v ++)
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

void solve()
{
	memset(c, 0, sizeof(c));
	scanf("%d%d%d%d", &n, &np, &nc, &m);
	if(feof(stdin))
		return;
	src = n + 1, sink = n + 2;
	for(int i = 1, u, v, t; i <= m; i ++)
	{
		scanf("%*[^(](%d,%d)%d", &u, &v, &t);
		u ++, v ++;
		c[u][v] += t;
	}
	for(int i = 1, u, t; i <= np; i ++)
	{
		scanf("%*[^(](%d)%d", &u, &t);
		u ++;
		c[src][u] += t;
	}
	for(int i = 1, u, t; i <= nc; i ++)
	{
		scanf("%*[^(](%d)%d", &u, &t);
		u ++;
		c[u][sink] += t;
	}
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

int main()
{
	freopen("t.in", "r", stdin);
	while(! feof(stdin))
		solve();
}
