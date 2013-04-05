#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge
{
	int vtx, len;
	bool enable;
	Edge *next, *inv;
};

const int N_NODE_MAX = 10010;
const int N_EDGE_MAX = 2 * N_NODE_MAX;

Edge edge[N_EDGE_MAX], *begin[N_NODE_MAX];
int n_node, edge_idx;
int seq[N_NODE_MAX], n_seq;
int size[N_NODE_MAX], pre[N_NODE_MAX], depth[N_NODE_MAX];
int upperlim, ans;

Edge *make_edge(int u, int v, int w)
{
	Edge *e = &edge[edge_idx ++];
	e->vtx = v, e->len = w, e->next = begin[u];
	e->enable = true;
	return begin[u] = e;
}

void add_edge(int u, int v, int w)
{
	Edge *e1 = make_edge(u, v, w),
		 *e2 = make_edge(v, u, w);
	e1->inv = e2, e2->inv = e1;
}

void set_root(int root)
{
	static int queue[N_NODE_MAX];
	static bool vis[N_NODE_MAX];
	int qh = 0, qt = 0;
	memset(vis, 0, sizeof(bool) * n_node);

	queue[qt ++] = root;
	n_seq = 0;
	vis[root] = true;
	depth[root] = 0;
	pre[root] = -1;
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[n_seq ++] = u;
		size[u] = 0;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->enable)
			{
				int v = e->vtx;
				if(! vis[v])
				{
					depth[v] = depth[u] + e->len;
					pre[v] = u;
					vis[v] = true;
					queue[qt ++] = v;
				}
			}
	}
	for(int i = n_seq - 1; i >= 0; i --)
	{
		int u = seq[i];
		size[u] ++;
		if(pre[u] != -1)
			size[pre[u]] += size[u];
	}
}

void get_seq(int root)
{
	static int queue[N_NODE_MAX];
	int qh = 0, qt = 0;
	n_seq = 0;
	queue[qt ++] = root;
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[n_seq ++] = u;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->enable)
			{
				int v = e->vtx;
				if(v == pre[u])
					continue;
				queue[qt ++] = v;
			}
	}
}

int find_core(int root)
{
	static int f[N_NODE_MAX];
	set_root(root);
	for(int i = 0; i < n_seq; i ++)
		f[i] = 0;
	for(int i = 0; i < n_seq; i ++)
	{
		int u = seq[i];
		if(u != root)
		{
			f[pre[u]] = max(f[pre[u]], size[u]);
			f[u] = max(f[u], size[root] - size[u]);
		}
	}
	int res = seq[0];
	for(int i = 1; i < n_seq; i ++)
		if(f[seq[i]] < f[res])
			res = seq[i];
	return res;
}

int count_pair()
{
	static int a[N_NODE_MAX];
	for(int i = 0; i < n_seq; i ++)
		a[i] = depth[seq[i]];
	sort(a, a + n_seq);
	int res = 0;
	for(int i = 1, j = 0; i < n_seq; i ++, j ++)
	{
		while(j >= 0 && a[j] + a[i] > upperlim)
			j --;
		res += j + 1;
	}
	return res;
}
vector<int> son[N_NODE_MAX];
void work(int u)
{
	u = find_core(u);
	set_root(u);
	ans += count_pair();
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->enable)
		{
			int v = e->vtx;
			son[u].push_back(v);
			e->enable = e->inv->enable = false;
			get_seq(v);
			ans -= count_pair();
		}
	for(int i = 0; i < (int) son[u].size(); i ++)
		work(son[u][i]);
}

int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	n_node = n;
	memset(begin, 0, sizeof(Edge*) * n_node);
	for(int i = 0; i < n; i ++)
		son[i].clear();
	edge_idx = 0;
	for(int i = 0; i < n - 1; i ++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		add_edge(u, v, w);
	}
	scanf("%d", &upperlim);
	ans = 0;
	work(0);
	printf("%d\n", ans);
}
