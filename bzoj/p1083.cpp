#include <cstdio>
#include <cstring>
const int N_MAX = 300;
struct Edge
{
	int vtx, weight;
	Edge *next;
};
Edge edge[N_MAX * N_MAX * 2], *begin[N_MAX];
int upperlim, n_vtx, n_edge;
bool vis[N_MAX];

void add_edge(int u, int v, int weight)
{
	Edge *e = &edge[n_edge ++];
	e->next = begin[u], e->vtx = v, e->weight = weight;
	begin[u] = e;
}

void dfs(int u)
{
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->weight <= upperlim)
		{
			int v = e->vtx;
			if(! vis[v])
				dfs(v);
		}
}
bool check(int k)
{
	upperlim = k;
	memset(vis, 0, sizeof(bool) * n_vtx);
	dfs(0);
	for(int i = 0; i < n_vtx; i ++)
		if(! vis[i])
			return false;
	return true;
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int m;
	scanf("%d%d", &n_vtx, &m);
	while(m --)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		u --, v --;
		add_edge(u, v, c);
		add_edge(v, u, c);
	}
	int l = 1, r = 10001, mid = (l + r) / 2, ans;
	while(l < r)
	{
		if(check(mid))
		{
			ans = mid;
			r = mid;
		}
		else
			l = mid + 1;
		mid = (l + r) / 2;
	}
	printf("%d %d\n", n_vtx - 1, ans);
}
