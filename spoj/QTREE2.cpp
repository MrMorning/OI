#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N_NODE_MAX = 10010;
const int N_SEQ_MAX = 2 * N_NODE_MAX;

namespace rmq
{
	int log2[N_SEQ_MAX];
	int st[N_SEQ_MAX][30];

	void init();
	int lca(int u, int v);
}

struct Edge
{
	int vtx, weight;
	Edge *next;
};

Edge edge[N_NODE_MAX * 2], *begin[N_NODE_MAX];
int n_edge, n_node;

int seq[N_SEQ_MAX];
int n_seq;

int depth[N_NODE_MAX];
int ancestor[N_NODE_MAX][30];
int pos[N_NODE_MAX];
int dist[N_NODE_MAX];

void add_edge(int u, int v, int weight)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->weight = weight, e->next = begin[u];
	begin[u] = e;
}

void rmq::init()
{
	for(int i = 0; 1 << i < N_SEQ_MAX; i ++)
		log2[1 << i] = i;
	for(int i = 0; i < N_SEQ_MAX; i ++)
		log2[i] = log2[i] ? log2[i]: log2[i - 1];

	for(int i = 0; i < n_seq; i ++)
		st[i][0] = seq[i];

	for(int j = 1; (1 << j) <= n_seq; j ++)
		for(int i = 0; i < n_seq; i ++)
		{
			int tmp = i + (1 << (j - 1));
			st[i][j] = st[i][j - 1];
			if(tmp >= n_seq)
				continue;
			if(depth[st[tmp][j - 1]] < depth[st[i][j]])
				st[i][j] = st[tmp][j - 1];
		}
}

int rmq::lca(int u, int v)
{
	int l = pos[u], r = pos[v];
	if(l > r)
		swap(l, r);
	int k = log2[r - l + 1];
	int len = 1 << k;
	int ret = st[l][k];
	if(depth[ret] > depth[st[r - len + 1][k]])
		ret = st[r - len + 1][k];
	return ret;
}

void dfs(int u, int p, int weight)
{
	seq[n_seq ++] = u;
	pos[u] = n_seq - 1;
	depth[u] = p != -1 ? depth[p] + 1 : 0; 
	dist[u] = p != -1 ? dist[p] + weight : 0;
	ancestor[u][0] = p;
	for(int k = 1; ; k ++)
	{
		int tmp = ancestor[u][k - 1];
		if(tmp == -1)
			break;
		ancestor[u][k] = ancestor[tmp][k - 1];
	}
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(v == p)
			continue;
		dfs(v, u, e->weight);
		seq[n_seq ++] = u;
	}
}

int ask_ancestor(int u, int k)
{
	int cnt = -1;
	while(k)
	{
		cnt ++;
		if(k & 1)
			u = ancestor[u][cnt];
		if(u == -1)
			return -1;
		k >>= 1;
	}
	return u;
}

void solve()
{
	n_edge = 0;
	n_seq = 0;
	scanf("%d", &n_node);
	memset(begin, 0, sizeof(Edge *) * n_node);
	for(int i = 0; i < n_node; i ++)
		memset(ancestor[i], -1, sizeof(ancestor[i]));
	for(int i = 0; i < n_node - 1; i ++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs(0, -1, -1);
	rmq::init();
	while(1)
	{
		static char cmd[10];
		scanf("%s", cmd);
		if(cmd[1] == 'O')
			break;
		if(cmd[1] == 'I')
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u --, v --;
			int p = rmq::lca(u, v);
			printf("%d\n", dist[u] - dist[p] + dist[v] - dist[p]);
		}
		else
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u --, v --;
			int p = rmq::lca(u, v);
			int t = ask_ancestor(u, w - 1);
			if(t == -1 || depth[t] < depth[p])
				t = ask_ancestor(v, -2 * depth[p] + depth[u] + depth[v] + 1 - w);
			printf("%d\n", t + 1);
		}
	}
	printf("\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
		solve();
}
