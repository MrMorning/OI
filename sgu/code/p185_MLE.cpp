#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int E_MAX = 320010;
const int V_MAX = 410;
const int oo = 0x3f3f3f3f;

struct Edge
{
	short to, cap, cost;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX], *prev[V_MAX];
int dist[V_MAX];
int edgeCnt, pathCnt;
int path[V_MAX];
int sv, tv, nv;

Edge *makeEdge(int u, int v, int c, int w)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], e->cap = c, e->cost = w;
	return begin[u] = e;
}

void addEdge(int u, int v, int c, int w)
{
	Edge *e1 = makeEdge(u, v, c, w),
		 *e2 = makeEdge(v, u, 0, -w);
	e1->inv = e2, e2->inv = e1;
}

void spfa()
{
	static int queue[V_MAX];
	static bool inQ[V_MAX];

	memset(inQ, 0, sizeof(bool) * nv);
	memset(dist, 0x3f, sizeof(int) * nv);
	memset(prev, 0, sizeof(Edge*) * nv);

	int qh = 0, qt = 0;
	queue[qt ++] = sv;
	inQ[sv] = true;
	
	dist[sv] = 0;
	while(qh != qt)
	{
		int u = queue[qh];
		inQ[u] = false;
		qh = (qh + 1) % nv;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->to;
				if(dist[v] > dist[u] + e->cost)
				{
					dist[v] = dist[u] + e->cost;
					prev[v] = e;
					if(!inQ[v])
					{
						inQ[v] = true;
						queue[qt] = v;
						qt = (qt + 1) % nv;
					}
				}
			}
	}
}

int costFlow()
{
	int res = 0;
	while(1)
	{
		spfa();
		if(dist[tv] == oo)
			break;
		int flow = oo;
		for(Edge *e = prev[tv]; e; e = prev[e->inv->to])
			flow = min(flow, (int)e->cap);
		for(Edge *e = prev[tv]; e; e = prev[e->inv->to])
		{
			e->cap -= flow, e->inv->cap += flow;
			res += flow * e->cost;
		}
	}
	return res;
}

void dfs(int u)
{
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->cost >= 0 && e->inv->cap > 0)
		{
			path[pathCnt ++] = e->to;
			e->inv->cap --;
			dfs(e->to);
			break;
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	int ne;
	scanf("%d%d", &nv, &ne);
	while(ne --)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		addEdge(u, v, 1, w);
		addEdge(v, u, 1, w);
	}
	sv = nv, tv = nv + 1;
	addEdge(sv, 0, 1, 0);
	Edge *se = &edge[edgeCnt - 2];
	addEdge(nv - 1, tv, 1, 0);
	Edge *te = &edge[edgeCnt - 2];
	nv += 2;
	int minDist = costFlow();
	se->cap ++, te->cap ++;
	int tmp = costFlow();
	if(minDist == 0 || minDist != tmp)
		printf("No solution\n");
	else
	{
		pathCnt = 0;
		path[pathCnt ++] = sv;
		dfs(sv);
		for(int i = 1; i < pathCnt - 1; i ++)
			printf("%d ", path[i] + 1);
		printf("\n");
		pathCnt = 0;
		path[pathCnt ++] = sv;
		dfs(sv);
		for(int i = 1; i < pathCnt - 1; i ++)
			printf("%d ", path[i] + 1);
	}
}
