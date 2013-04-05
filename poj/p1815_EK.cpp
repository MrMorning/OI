#include <cstdio>
#include <cstring>
#include <queue>
#define ST(x) ((x)*2-1)
#define EN(x) ((x)*2)
#define MAXN 410
#define INF 0x3f3f3f3f
using std::queue;
int flow[MAXN], prev[MAXN], c[MAXN][MAXN], c_t[MAXN][MAXN];
int src, sink, n, ans[MAXN], ansNum;
bool vis[MAXN];

inline int min(int a, int b)
{
	return a < b ? a: b;
}

int findArg()
{
	memset(vis, 0, sizeof(vis));
	memset(prev, 0, sizeof(prev));
	queue<int> q;
	q.push(ST(src));
	vis[ST(src)] = true;
	flow[ST(src)] = INF;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == EN(sink))
			return flow[u];
		for(int v = 1; v <= 2 * n; v ++)
			if(! vis[v] && c_t[u][v])
			{
				vis[v] = true;
				flow[v] = min(flow[u], c_t[u][v]);
				prev[v] = u;
				q.push(v);
			}
	}
	return 0;
}

int maxFlow()
{
	memcpy(c_t, c, sizeof(c));
	int ans = 0;
	while(int tmp = findArg())
	{
		ans += tmp;
		int v = EN(sink);
		while(int u = prev[v])
		{
			c_t[u][v] -= tmp;
			c_t[v][u] += tmp;
			v = u;
		}
	}
	return ans;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &src, &sink);
	for(int i = 1; i <= n; i ++)
		for(int j = 1, t; j <= n; j ++)
		{
			scanf("%d", &t);
			if(i == j || t == 0)
				continue;
			c[EN(i)][ST(j)] = INF;
		}
	for(int i = 1; i <= n; i ++)
		if(i != src && i != sink)
			c[ST(i)][EN(i)] = 1;
		else
			c[ST(i)][EN(i)] = INF;
	int cnt = maxFlow();
	for(int u = 1; u <= n; u ++)
	{
		if(u == src || u == sink)
			continue;
		c[ST(u)][EN(u)] = 0;
		if(maxFlow() == cnt - 1)
		{
			cnt --;
			ans[++ ansNum] = u;
			if(cnt == 0)
				break;
		}
		else
			c[ST(u)][EN(u)] = 1;
	}
	if(cnt > 0)
		printf("NO ANSWER!\n");
	else
	{
		printf("%d\n", ansNum);
		for(int i = 1; i < ansNum; i ++)
			printf("%d ", ans[i]);
		printf("%d\n", ans[ansNum]);
	}
}
