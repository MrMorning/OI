#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V_MAX = 16000;
const int oo = 0x3f3f3f3f;

struct Edge
{
	int to;
	Edge *next;
} edge[V_MAX * 2], *begin[V_MAX];
int w[V_MAX], f[V_MAX], pre[V_MAX];
int seq[V_MAX], queue[V_MAX];
int edgeCnt, seqCnt;
int np;

void addEdge(int u, int v)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &np);
	for(int i = 0; i < np; i ++)
		scanf("%d", &w[i]);
	for(int i = 0, a, b; i < np - 1; i ++)
	{
		scanf("%d%d", &a, &b);
		a --, b --;
		addEdge(a, b), addEdge(b, a);
	}

	int qt = 0, qh = 0;
	queue[qt ++] = 0;
	memset(pre, -1, sizeof(pre));
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[seqCnt ++] = u;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(v == pre[u])
				continue;
			pre[v] = u;
			queue[qt ++] = v;
		}
	}

	int ans = -oo;
	for(int i = seqCnt - 1; i >= 0; i --)
	{
		int u = seq[i];
		f[u] += w[u];
		if(pre[u] != -1)
			f[pre[u]] += max(f[u], 0);
		ans = max(ans, f[u]);
	}

	printf("%d\n", ans);
}
