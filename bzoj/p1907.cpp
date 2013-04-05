#include <cstdio>
#include <cstring>

struct Edge
{
	int to;
	Edge *next;
};

const int N_VTX_MAX = 10010;
const int N_EDGE_MAX = 2 * N_VTX_MAX;

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
int n_edge, n_vtx;
int cnt[N_VTX_MAX];
int ans;

void add_edge(int a, int b)
{
	Edge *e = &edge[n_edge ++];
	e->to = b, e->next = begin[a], begin[a] = e;
}

void dfs(int u, int p)
{
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(v != p)
			dfs(v, u);
	}
	if(cnt[u] == 0)
		ans ++, cnt[p] ++;
	else if(cnt[u] == 1)
		cnt[p] ++;
	else
		ans --;
}

void solve()
{
	scanf("%d", &n_vtx);
	n_edge = 0;
	ans = 0;
	memset(begin, 0, sizeof(begin));
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0, a, b;i < n_vtx - 1; i ++)
	{
		scanf("%d%d", &a, &b);
		add_edge(a, b);
		add_edge(b, a);
	}
	dfs(1, 0);
	printf("%d\n", ans);
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
