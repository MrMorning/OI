#include <cstdio>
#include <algorithm>
using namespace std;

const int V_MAX = 10000;

struct Edge
{
	int to;
	Edge *next;
} *begin[V_MAX];

struct State
{
	int idx, val;
	State(int _idx = 0, int _val = 0):
		idx(_idx), val(_val){}
};

int pre[V_MAX], weight[V_MAX];
int seq[V_MAX], seqCnt, nv;
State f[V_MAX], g[V_MAX];
int h[V_MAX];

void addEdge(int u, int v)
{
	static int edgeCnt = 0;
	static Edge edge[V_MAX];
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

void bfs()
{
	static int queue[V_MAX];
	int qh = 0, qt = 0;
	queue[qt ++] = 0;
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[seqCnt ++] = u;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			queue[qt ++] = v;
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	pre[0] = -1;
	for(int i = 1, p, c; i < nv; i ++)
	{
		scanf("%d%d", &p, &c);
		pre[i] = p - 1;
		weight[i] = c;
		addEdge(p - 1, i);
	}
	bfs();
	for(int i = 0; i < nv; i ++)
		f[i] = g[i] = State(i, 0);
	for(int i = seqCnt - 1; i >= 1; i --)
	{
		int u = seq[i];
		int p = pre[u];
		if(f[u].val + weight[u] > f[p].val)
		{
			g[p] = f[p];
			f[p] = State(u, f[u].val + weight[u]);
		}
		else if(f[u].val + weight[u] > g[p].val)
			g[p] = State(u, f[u].val + weight[u]);
	}

	for(int i = 0; i < seqCnt; i ++)
	{
		int u = seq[i];
		h[u] = pre[u] == -1 ? 0 : h[pre[u]] + weight[u];
		if(u)
		{
			State tmp = f[pre[u]];
			if(tmp.idx == u)
				tmp = g[pre[u]];
			if(tmp.val + weight[u] > h[u])
				h[u] = tmp.val + weight[u];
		}
	}

	for(int i = 0; i < nv; i ++)
		printf("%d\n", max(h[i], f[i].val));
}
