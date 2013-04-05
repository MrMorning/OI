#include <cstdio>
#include <cstdlib>
#include <cstring>

const int V_MAX = 201;
const int E_MAX = 60010;

struct Edge
{
	Edge *next;
	int to;
} *begin[V_MAX];

void addEdge(int u, int v)
{
	static Edge edge[E_MAX];
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

int n, m;
int color[V_MAX];

void dfs(int u, int c)
{
	color[u] = c;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(color[v] == -1)
			dfs(v, !c);
		else if(color[v] == c)
		{
			printf("no\n");
			exit(0);
		}
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	while(m --)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
	memset(color, -1, sizeof(color));
	for(int i = 1; i <= n; i ++)
		if(color[i] == -1)
			dfs(i, 0);
	int cnt = 0;
	for(int i = 1; i <= n; i ++)
		if(color[i] == 0)
			cnt ++;
	printf("yes\n%d\n", cnt);
	for(int i = 1; i <= n; i ++)
		if(color[i] == 0)
			printf("%d ", i);
}
