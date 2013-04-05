#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

const int V_MAX = 500000;

struct Edge
{
	int to;
	Edge *next;
} edge[V_MAX], *begin[V_MAX];
int nv, seqCnt, seq[V_MAX];
int queue[V_MAX];
int ans[V_MAX], ansCnt;
int pre[V_MAX];
int f[V_MAX][2], g[V_MAX];

void addEdge(int u, int v)
{
	static int freePos = 0;
	Edge *e = &edge[freePos ++];
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for(int i = 1; i < nv; i ++)
	{
		int p;
		scanf("%d", &p);
		p --;
		addEdge(p, i);
	}

	int qh = 0, qt = 0;
	queue[qt ++] = 0;
	pre[0] = -1;
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[seqCnt ++] = u;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			pre[e->to] = u;
			queue[qt ++] = e->to;
		}
	}
	for(int i = 0; i < nv; i ++)
		f[i][0] = 0, f[i][1] = 0, g[i] = -1;
	for(int i = seqCnt - 1; i >= 0; i --)
	{
		int u = seq[i];
		if(g[u] != -1)
			f[u][1] += f[u][0] + 1;
		assert(f[u][1] >= f[u][0]);
		int p = pre[u];
		if(p == -1)
			continue;
		f[p][0] += f[u][1];
		if(g[p] == -1 || f[u][0] - f[u][1] > f[p][1])
			f[p][1] = f[u][0] - f[u][1], g[p] = u;
	}

	printf("%d000\n", f[0][1]);
	qh = qt = 0;
	queue[qt ++] = 0;
	while(qh < qt)
	{
		int u = queue[qh ++];
		if(g[u] == -1)
			continue;
		ans[ansCnt ++] = g[u];
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(v != g[u])
				queue[qt ++] = v;
		}

		for(Edge *e = begin[g[u]]; e; e = e->next)
		{
			int v = e->to;
			if(g[v] != -1)
				queue[qt ++] = v;
		}
	}
	sort(ans, ans + ansCnt);
	for(int i = 0; i < ansCnt; i ++)
		printf("%d ", ans[i] + 1);
}
