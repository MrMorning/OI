#include <cstdio>
#include <cstring>
#include <algorithm>
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
int n_node, edge_idx, upperlim;
int seq[2 * N_NODE_MAX], n_seq;
int weight[N_NODE_MAX], pre[N_NODE_MAX], pos[N_NODE_MAX], depth[N_NODE_MAX];
int log2[2 * N_NODE_MAX];
int st[2 * N_NODE_MAX][30];
bool vis[N_NODE_MAX];


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

void dfs(int u)
{
	vis[u] = true;
	seq[n_seq ++] = u;
	pos[u] = n_seq - 1;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! vis[v])
		{
			pre[v] = u;
			weight[v] = e->len;
			depth[v] = depth[u] + 1;
			dfs(v);
			seq[n_seq ++] = u;
		}
	}
}

void init_st()
{
	for(int i = 0; i < n_seq; i ++)
		st[i][0] = seq[i];
	for(int j = 1; (1 << j) <= n_seq; j ++)
		for(int i = 0; i < n_seq; i ++)
		{
			st[i][j] = st[i][j - 1];
			if(i + (1 << (j - 1)) >= n_seq)
				continue;
			if(depth[st[i + (1 << (j - 1))][j - 1]] < depth[st[i][j]])
				st[i][j] = st[i + (1 << (j - 1))][j - 1];
		}
	for(int i = 0; (1 << i) <= n_seq; i ++)
		log2[1 << i] = i;
	for(int i = 1; i < n_seq; i ++)
		if(log2[i] == 0)
			log2[i] = log2[i - 1];
}

int lca(int u, int v)
{
	int a = min(pos[u], pos[v]),
		b = max(pos[u], pos[v]);
	int len = b - a + 1;
	int res = st[a][log2[len]];
	if(depth[st[b - (1 << log2[len]) + 1][log2[len]]] < depth[res])
		res = st[b - (1 << log2[len]) + 1][log2[len]];
	return res;
}

int work()
{
	n_seq = 0;
	memset(vis, 0, sizeof(vis));
	dfs(0);
	init_st();
	int res = 0;
	for(int i = 0; i < n_node; i ++)
		for(int j = i + 1; j < n_node; j ++)
		{
			int u = i, v = j;
			int p = lca(u, v);
			int cnt = 0;
			while(u != p)
			{
				cnt += weight[u]; 
				u = pre[u];
			}
			while(v != p)
			{
				cnt += weight[v]; 
				v = pre[v];
			}
			if(cnt <= upperlim)
				res ++;
		}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		int n;
		scanf("%d%d", &n, &upperlim);
		if(n == 0 && upperlim == 0)
			break;
		n_node = n;
		memset(begin, 0, sizeof(Edge*) * n_node);
		edge_idx = 0;
		for(int i = 0; i < n - 1; i ++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u --, v --;
			add_edge(u, v, w);
		}
		printf("%d\n", work());
	}
}
