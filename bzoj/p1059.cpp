#include <cstdio>
#include <cstring>

const int N_VTX_MAX = 400;

struct Edge
{
	int vtx;
	Edge *next;
} edge[N_VTX_MAX * N_VTX_MAX], *begin[N_VTX_MAX];
int free_pos;
bool vis[N_VTX_MAX];
int match[N_VTX_MAX];

void add_edge(int u, int v)
{
	Edge *e = &edge[free_pos ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}

bool dfs(int u)
{
	for(Edge *e = begin[u]; e; e = e->next)
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

void solve()
{
	memset(begin, 0, sizeof(begin));
	memset(match, -1, sizeof(match));
	free_pos = 0;
	int n;
	scanf("%d", &n);
	int n_vtx = 2 * n;
	for(int i = 0; i < n; i ++)
		for(int j = 0, t; j < n; j ++)
		{
			scanf("%d", &t);
			if(t)
				add_edge(i, n + j), add_edge(n + j, i);
		}
	int ans = 0;
	for(int i = 0; i < n; i ++)
	{
		memset(vis, 0, sizeof(bool) * n_vtx);
		if(dfs(i))
			ans ++;
	}
	if(ans >= n)
		printf("Yes\n");
	else
		printf("No\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
