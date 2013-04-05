#include <cstdio>
#include <cstring>
#include <queue>
#define ST(x) ((x)*2-1)
#define EN(x) ((x)*2)
#define MAXN 410
#define INF 0x3f3f3f3f
using std::queue;
int flow[MAXN], pre[MAXN], c[MAXN][MAXN], c_t[MAXN][MAXN];
int level[MAXN], stk[MAXN]; 
int src, sink, n, m, st, en, ans[MAXN], ansNum;
bool vis[MAXN];

inline int min(int a, int b)
{
	return a < b ? a: b;
}

bool bfs()
{
	memset(level, 0, sizeof(level));
	queue<int> q;
	q.push(src);
	level[src] = 1;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == sink)
			return true;
		for(int v = 1; v <= 2 * n; v ++)
			if(! level[v] && c_t[u][v])
			{
				level[v] = level[u] + 1;
				q.push(v);
			}
	}
	return false;
}

inline bool linked(int u, int v)
{
	return level[u] + 1 == level[v] && c_t[u][v];
}

int outD(int u)
{
	int cnt = 0;
	for(int v = 1; v <= 2 * n; v ++)
		if(linked(u, v))
			cnt ++;
	return cnt;
}
int maxFlow()
{
	memcpy(c_t, c, sizeof(c));
	int ans = 0;
	while(bfs())
	{
		int top = 0;
		stk[++ top] = src;
		memset(pre, 0, sizeof(pre));
		flow[src] = INF;
		while(outD(src) != 0)
		{
			int u = stk[top];
			if(u != sink)
			{
				if(outD(u) > 0)
				{
					for(int v = 1; v <= 2 * n; v ++)
						if(linked(u, v))
							stk[++ top] = v, flow[v] = min(flow[u], c_t[u][v]), pre[v] = u;
				}
				else
				{
					top --;
					level[u] = INF;
				}
			}
			else
			{
				int v = sink;
				int arg = flow[sink], last;
				ans += arg;
				while(int w = pre[v])
				{
					c_t[w][v] -= arg;
					c_t[v][w] += arg;
					if(c_t[w][v] == 0)
						last = w;
					v = w;
				}
				while(stk[top] != last)
					top --;
			}
		}
	}
	return ans;
}

int findArg()
{
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(src);
	vis[src] = true;
	flow[src] = INF;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		if(u == sink)
			return flow[sink];
		for(int v = 1; v <= 2 * n; v ++)
			if(! vis[v] && c_t[u][v])
			{
				vis[v] = true;
				flow[v] = min(flow[u], c_t[u][v]);
				pre[v] = u;
				q.push(v);
			}
	}
	return 0;
}

int EK()
{
	memcpy(c_t, c, sizeof(c));
	int ans = 0;
	while(int tmp = findArg())
	{
		ans += tmp;
		int v = sink;
		while(int u = pre[v])
		{
			c_t[u][v] -= tmp;
			c_t[v][u] += tmp;
			v = u;
		}
	}
	return ans;
}

void solve()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &st, &en);
	src = ST(st), sink = EN(en);
	for(int i = 1; i <= n; i ++)
		for(int j = 1, t; j <= n; j ++)
		{
			scanf("%d", &t);
			if(t == 0)
				continue;
			c[EN(i)][ST(j)] = INF;
		}
	for(int i = 1; i <= n; i ++)
		if(i != st && i != en)
			c[ST(i)][EN(i)] = 1;
		else
			c[ST(i)][EN(i)] = INF;
	int cnt = maxFlow();
	for(int u = 1; u <= n; u ++)
	{
		if(u == st || u == en)
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
		if(ansNum > 0)
			printf("%d\n", ans[ansNum]);
	}
}

void debug()
{
	freopen("test.in", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &src, &sink);
	for(int i = 1, a, b, t; i <= m; i ++)
	{
		scanf("%d%d%d", &a, &b, &t);
		c[a][b] = t;
	}
	printf("%d\n", maxFlow());
}

int main()
{
	//	debug();
	solve();
}
