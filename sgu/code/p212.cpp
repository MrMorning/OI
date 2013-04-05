#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#define REP(i, n) for(int i = 0; i < (n); i ++)
using namespace std;

const int V_MAX = 1500;
const int E_MAX = 300000;
const int oo = 0x3f3f3f3f;

struct Edge
{
	int to, cap, flow;
	Edge *next;
} edge[E_MAX], *begin[V_MAX], *pe[E_MAX];

int nv, ne, sv, tv;
int level[V_MAX];
int edgeCnt;

void addEdge(int u, int v, int w)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
	e->flow = 0;
	e->cap = w;
}

int findAug(int u, int flow)
{
	if(u == tv)
		return flow;
	int res = 0;
	Edge *e;
	for(e = begin[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->to;
			if(level[v] != level[u] + 1)
				continue;
			int tmp = findAug(v, min(flow, e->cap));
			if(tmp)
			{
				flow -= tmp;
				e->cap -= tmp, e->flow += tmp;
				res += tmp;
			}
			if(!flow)
				break;
		}
	return res;
}

void bfs()
{
	static int queue[V_MAX];
	static int power[V_MAX];
	static bool inQ[V_MAX];
	int qh = 0, qt = 0;
	queue[qt ++] = sv;
	power[sv] = oo;
	inQ[sv] = true;
	while(qh < qt)
	{
		int u = queue[qh ++];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->to;
				if(level[v] != level[u] + 1)
					continue;
				int t = min(power[u], e->cap);
				e->cap -= t, e->flow += t;
				power[u] -= t;
				power[v] += t;
				if(!inQ[v])
				{
					inQ[v] = true;
					queue[qt ++] = v;
				}
			}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int L;
	scanf("%d%d%d", &nv, &ne, &L);
	REP(i, nv)
	{
		scanf("%d", &level[i]);
		if(level[i] == 1)
			sv = i;
		if(level[i] == L)
			tv = i;
	}
	REP(i, ne)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		addEdge(u, v, w);
		pe[i] = &edge[edgeCnt - 1];
	}
	bfs();
	while(findAug(sv, oo));
	REP(i, ne)
		printf("%d\n", pe[i]->flow);
}
