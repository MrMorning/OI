#include <cstdio>
#include <cstring>

namespace Solve
{
	const int MAX_VTX = 1000,
		  MAX_EDGE = MAX_VTX * MAX_VTX;
	struct Edge
	{
		int vtx;
		Edge *next;
	} edge[MAX_EDGE], *begin[MAX_VTX];
	int dfn[MAX_VTX], low[MAX_VTX];
	void addEdge(int u, int v);
	void dfs(int u);
	void solve(FILE*, FILE*);
}

Solve::addEdge(int u, int v)
{
	exist[u] = exist[v] = true;
	edge[nEdge].vtx = v, edge[nEdge].next = begin[u];
	begin[u] = &edge[nEdge ++];
}

void Solve::dfs(int u)
{
	static int idx = 0;
	dfn[u] = low[u] = ++ idx;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! dfn[v])
		{
			dfs(v);
			low[u] = MIN(low[u], low[v]);
		}
		else 
			low[u] = MIN(low[u], dfn[v]);
	}
}

void Solve::solve(FILE *fin, FILE *fout)
{
	while(1)
	{
		fscanf(fin, "%d", &u);
		if(u == 0)
			break;
		fscanf(fin, "%d", &v);
		memset(begin, 0, sizeof(begin));
		memset(exist, 0, sizeof(exist));
		nEdge = 0;
		addEdge(u, v), addEdge(v, u);
		while(1)
		{
			fscanf(fin, "%d", &u);
			if(u == 0)
				break;
			fscanf(fin, "%d", &v);
			addEdge(u, v), addEdge(v, u);
		}

	}
