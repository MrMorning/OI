#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


struct Edge
{
	Edge *next;
	int to;
};

const int N_VTX_MAX = 20010, N_EDGE_MAX = 20010;

int n_node, f[N_VTX_MAX], size[N_VTX_MAX], pre[N_VTX_MAX];
int edge_idx;

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];

void add_edge(int u, int v)
{
	Edge *e = &edge[edge_idx ++];
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

void dfs(int u, int p)
{
	pre[u] = p;
	size[u] = 1;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(v == p)
			continue;
		dfs(v, u);
		size[u] += size[v];
	}
}

void solve()
{
	edge_idx = 0;
	memset(begin, 0, sizeof(begin));
	scanf("%d", &n_node);
	for(int i = 1, a, b; i < n_node; i ++)
	{
		scanf("%d%d", &a, &b);
		add_edge(a, b), add_edge(b, a);
	}
	dfs(1, 0);
	memset(f, 0, sizeof(f));
	for(int i = 1; i <= n_node; i ++)
	{
		int p = pre[i];
		if(p)
			if(size[i] > f[pre[i]])
				f[pre[i]] = size[i];
		f[i] = max(f[i], size[1] - size[i]);
	}
	int ans = 1;
	for(int i = 2; i <= n_node; i ++)
		if(f[i] < f[ans])
			ans = i;
	printf("%d %d\n", ans, f[ans]);
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
