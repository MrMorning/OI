#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define VTX_MAX 1010000
#define EDGE_MAX 4000000
struct edge_t
{
	int vtx;
	edge_t *next;
} edge[EDGE_MAX], *begin[VTX_MAX];
int match[VTX_MAX], nEdge;
bool vis[VTX_MAX];
void makeEdge(int u, int v)
{
	edge_t *e = &edge[nEdge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}
void addEdge(int u, int v)
{
	makeEdge(u, v), makeEdge(v, u);
}
bool dfs(int u)
{
	for(edge_t *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! vis[v])
		{
			vis[v] = true;
			if(match[v] == -1 || dfs(match[v]))
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}
void inline readInt(int &x)
{
	x = 0;
	char ch = getchar();
	while(ch == ' ' || ch == '\n') ch = getchar();
	while('0' <= ch && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
}
int main()
{
	freopen("t.in", "r", stdin);
	int n, a, b;
	readInt(n);
	for(int i = 0; i < n; i ++)
	{
		readInt(a), readInt(b);
		if(a <= 10000)
			addEdge(a - 1, i + 10000);
		if(b <= 10000)
			addEdge(b - 1, i + 10000);
	}
	memset(match, -1, sizeof(int) * (10000 + n));
	int i;
	for(i = 0; i < 10000; i ++)
	{
		memset(vis, 0, sizeof(bool) * (10000 + n));
		if(! dfs(i))
			break;
	}
	printf("%d\n", i);
}
