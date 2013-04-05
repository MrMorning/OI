// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define FOR(I, A, B)	for(int I = (A); I < (B); I ++)
#define REP(I, N)	FOR(I, 0, N)
#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
#define ALL(I) (I).begin(), (I).end()
#define PB(X) push_back(X)

using namespace std;

typedef long long ll;

// }}}

const int V_MAX = 1010, E_MAX = 50010;

struct Edge
{
	int to, from, w;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];
int dfn[V_MAX], low[V_MAX];
bool marked[V_MAX];
bool inStack[V_MAX];
int nv, ne;
vector<int> scc[V_MAX];
int stack[V_MAX], queue[V_MAX];
int belong[V_MAX];
int sccIdx, top;
int weight[V_MAX][V_MAX];

void addEdge(int u, int v, int w)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->from = u, e->w = w;
	e->next = begin[u], begin[u] = e;
}

void tarjan(int u)
{
	static int dfnIdx = 0;
	dfn[u] = low[u] = dfnIdx ++;
	inStack[u] = true;
	stack[top ++] = u;
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->w == 0)
		{
			int v = e->to;
			if(dfn[v] == -1)
				tarjan(v), low[u] = min(low[u], low[v]);
			else if(inStack[v])
				low[u] = min(low[u], dfn[v]);
		}
	if(dfn[u] == low[u])
	{
		while(1)
		{
			int v = stack[-- top];
			belong[v] = sccIdx;
			scc[sccIdx].PB(v);
			inStack[v] = false;
			if(v == u)
				break;
		}
		sccIdx ++;
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &ne);
	memset(weight, -1, sizeof(weight));
	REP(i, ne)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		weight[u][v] = w;
		addEdge(u, v, w);
	}
	memset(dfn, -1, sizeof(dfn));
	memset(low, -1, sizeof(low));
	memset(belong, -1, sizeof(belong));
	REP(u, nv)
		if(dfn[u] == -1)
			tarjan(u);
	int qh = 0, qt = 0;
	REP(i, sccIdx)
		if(scc[i].size() > 1)
			FOREACH(j, scc[i])
				queue[qt ++] = *j;
		else
			if(weight[scc[i][0]][scc[i][0]] == 0)
				queue[qt ++] = scc[i][0];
	memset(marked, 0, sizeof(marked));
	FOR(i, qh, qt)
		marked[queue[i]] = true;
	while(qh < qt)
	{
		int u = queue[qh ++];
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(!marked[v])
			{
				marked[v] = true;
				queue[qt ++] = v;
			}
		}
	}
	REP(i, nv)
		printf("%d\n", !marked[i]);
}
