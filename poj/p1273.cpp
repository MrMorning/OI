#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define MAXN 201
using std::queue;

int c[MAXN][MAXN], flow[MAXN], prev[MAXN];
bool vis[MAXN];
int n, m;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int findArg()
{
	queue<int> q;
	memset(vis, 0, sizeof(vis));
	memset(prev, 0, sizeof(prev));
	q.push(1);
	vis[1] = true;
	flow[1] = INF;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == n)
			return flow[u];
		for(int v = 1; v <= n; v ++)
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

void solve()
{
	memset(c, 0, sizeof(c));
	scanf("%d %d\n", &m, &n);
	for(int i = 1, s, t, v; i <= m; i ++)
	{
		scanf("%d %d %d\n", &s, &t, &v);
		c[s][t] += v;
	}
	int ans = 0;
	while(int tmp = findArg())
	{
		ans += tmp;
		int v = n;
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
