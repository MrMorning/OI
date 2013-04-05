#include <cstdio>
#include <algorithm>
using namespace std;
const int N_MAX = 16000;
struct Edge
{
	int to;
	Edge *next;
} edge[N_MAX * 2], *begin[N_MAX];
int edgeCnt;

void addEdge(int u, int v)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
}

int n;
int pre[N_MAX], size[N_MAX], f[N_MAX];
int queue[N_MAX], ans[N_MAX], ansCnt;
int seq[N_MAX], seqCnt;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0, a, b; i < n - 1; i ++)
	{
		scanf("%d%d", &a, &b);
		a --, b --;
		addEdge(a, b);
		addEdge(b, a);
	}

	int qh = 0, qt = 0;
	queue[qt ++] = 0;
	pre[0] = -1;
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[seqCnt ++] = u;
		for(Edge *e = begin[u]; e; e = e ->next)
		{
			int v = e->to;
			if(v != pre[u])
			{
				pre[v] = u;
				queue[qt ++] = v;
			}
		}
	}

	for(int i = seqCnt - 1; i >= 0; i --)
	{
		int u = seq[i];
		size[u] ++;
		int p = pre[u];
		if(p != -1)
			size[p] += size[u], f[p] = max(f[p], size[u]);
	}

	int best = 0x3f3f3f3f;
	for(int i = 0; i < n; i ++)
	{
		f[i] = max(f[i], n - size[i]);
		best = min(best, f[i]);
	}

	for(int i = 0; i < n; i ++)
		if(f[i] == best)
			ans[ansCnt ++] = i;
	printf("%d %d\n", best, ansCnt);
	for(int i = 0; i < ansCnt; i ++)
		printf("%d ", ans[i] + 1);
}
