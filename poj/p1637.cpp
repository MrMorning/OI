#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define MAXN 210
using std::queue;
int n, m, src, sink, d[MAXN], c[MAXN][MAXN], prev[MAXN], flow[MAXN];
bool vis[MAXN];

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int findArg()
{
	memset(vis, 0, sizeof(vis));
	memset(prev, 0, sizeof(prev));
	queue<int> q;
	q.push(src);
	flow[src] = INF;
	vis[src] = true;
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

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d", &testNum);
	while(testNum --)
	{
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));
		scanf("%d%d", &n, &m);
		src = n + 1, sink = n + 2;
		for(int i = 1, u, v, flag; i <= m; i ++)
		{
			scanf("%d%d%d", &u, &v, &flag);
			if(flag == 1)
				d[u] --, d[v] ++;
			else
				d[u] --, d[v] ++, c[v][u] += 1;

		}
		bool failed = false;
		for(int i = 1; i <= n; i ++)
			if(d[i] & 1)
			{
				failed = true;
				break;
			}
		if(! failed)
		{
			for(int i = 1; i <= n; i ++)
				if(d[i] > 0)
					c[src][i] += d[i] >> 1;
				else if(d[i] < 0)
					c[i][sink] += (-d[i]) >> 1;
			while(int tmp = findArg())
			{
				int v = sink;
				while(prev[v])
				{
					int u = prev[v];
					c[u][v] -= tmp;
					c[v][u] += tmp;
					v = u;
				}
			}
			for(int i = 1 ; i <= n; i ++)
				if(c[src][i] != 0)
				{
					failed = true;
					break;
				}
		}
		if(failed)
			printf("impossible\n");
		else
			printf("possible\n");
	}
}
