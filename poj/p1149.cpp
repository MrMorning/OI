#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define MAXN 110
using std::queue;

int c[MAXN][MAXN], flow[MAXN], prev[MAXN], n, n1, n2, sink, src;
int pig[1001][MAXN], initPig[1001];
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

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n1, &n2);
	n = n2 + 2, src = n2 + 1, sink = src + 1;
	for(int i = 1; i <= n1; i ++)
		scanf("%d", &initPig[i]);
	for(int i = 1, t, m; i <= n2; i ++)
	{
		scanf("%d", &m);
		for(int j = 1, u; j <= m; j ++)
		{
			scanf("%d", &u);
			pig[u][++ pig[u][0]] = i;
		}
		scanf("%d", &t);
		c[i][sink] = t;
	}
	for(int i = 1; i <= n1; i ++)
		if(pig[i][0] > 0)
		{
			c[src][pig[i][1]] += initPig[i];
			for(int j = 1; j < pig[i][0]; j ++)
				c[pig[i][j]][pig[i][j + 1]] = INF;
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
