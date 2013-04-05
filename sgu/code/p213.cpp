#include <cstdio>
#include <vector>
#define FOR(i, l, r) for(int i = (l); i < (r); i ++)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) (x).begin(), (x).end()
#define FOREACH(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)
#define pb(x) push_back(x)
using namespace std;

struct Edge
{
	int idx, to;
	Edge *next;
} edge[160000], *begin[400];

void addEdge(int u, int v, int idx)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
	e->idx = idx;
}

int nv, ne, sv, tv, queue[400], dist[400], qh, qt;
vector<int> ans[400];
bool done[160000];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &nv, &ne, &sv, &tv);
	sv --, tv --;
	REP(i, ne)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u --, v --;
		addEdge(u, v, i);
		addEdge(v, u, i);
	}
	REP(i, nv)
		dist[i] = -1;
	qt = 0, qh = 0;
	queue[qt ++] = sv;
	dist[sv] = 0;
	while(qh < qt)
	{
		int u = queue[qh ++];
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(dist[v] == dist[u] + 1)
			{
				ans[dist[u]].pb(e->idx);
				done[e->idx] = true;
				continue;
			}
			if(dist[v] != -1)
				continue;
			dist[v] = dist[u] + 1;
			ans[dist[u]].pb(e->idx);
			done[e->idx] = true;
			queue[qt ++] = v;
		}
	}
	REP(i, ne)
		if(!done[i])
			ans[0].pb(i);
	printf("%d\n", dist[tv]);
	REP(i, dist[tv])
	{
		printf("%d", (int)ans[i].size());
		FOREACH(it, ans[i])
			printf(" %d", (*it) + 1);
		printf("\n");
	}
}
