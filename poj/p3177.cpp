#include <cstdio>
#include <cstring>
#include <set>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	const int MAX_VTX = 5000,
		  MAX_EDGE = 20000;
	struct Edge
	{
		int vtx;
		bool isBridge;
		Edge *next, *inverse;
	} edge[MAX_EDGE], *begin[MAX_VTX];
	int nVtx, nEdge, nComp;
	int dfn[MAX_VTX], low[MAX_VTX], parent[MAX_VTX];
	int dgr[MAX_VTX], belong[MAX_VTX];
	bool vis[MAX_VTX];

	Edge *makeEdge(int u, int v);
	void addEdge(int u, int v);
	void findBridge(int u);
	void dfs(int u);
	void solve(FILE*, FILE*);
}

Solve::Edge *Solve::makeEdge(int u, int v)
{
	edge[nEdge].vtx = v, edge[nEdge].next = begin[u];
	edge[nEdge].isBridge = false;
	return begin[u] = &edge[nEdge ++];
}

void Solve::addEdge(int u, int v)
{
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inverse = e2, e2->inverse = e1;
}

void Solve::findBridge(int u)
{
	static int idx = 0;
	dfn[u] = low[u] = ++ idx;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! dfn[v])
		{
			parent[v] = u;
			findBridge(v);
			low[u] = MIN(low[u], low[v]);
		}
		else if(dfn[v] < dfn[u])
			low[u] = MIN(low[u], dfn[v]);
		if(dfn[u] < low[v])
			e->isBridge = e->inverse->isBridge = true;
	}
}

void Solve::dfs(int u)
{
	vis[u] = true, belong[u] = nComp;
	for(Edge *e = begin[u]; e; e = e->next)
		if(! e->isBridge && ! vis[e->vtx])
			dfs(e->vtx);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int m;
	fscanf(fin, "%d%d", &nVtx, &m);
	std::set<std::pair<int, int> > S;
	for(int i = 0; i < m; i ++)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		if(S.count(std::make_pair(u - 1, v - 1)))
			continue;
		addEdge(u - 1, v - 1);
		S.insert(std::make_pair(u - 1, v - 1));
		S.insert(std::make_pair(v - 1, u - 1));
	}
	memset(dfn, 0, sizeof(int) * nVtx);
	for(int u = 0; u < nVtx; u ++)
	{
		if(! dfn[u])
			findBridge(u);
	}
	memset(vis, 0, sizeof(bool) * nVtx);
	memset(belong, 0, sizeof(int) * nVtx);
	for(int u = 0; u < nVtx; u ++)
		if(! vis[u])
		{
			dfs(u);
			nComp ++;
		}
	memset(dgr, 0, sizeof(int) * nComp);
	for(int i = 0; i < nEdge; i ++)
		if(edge[i].isBridge)
			dgr[belong[edge[i].vtx]] ++;
	int cnt = 0;
	for(int i = 0; i < nComp; i ++)
		if(dgr[i] == 1)
			cnt ++;
	fprintf(fout, "%d\n", (cnt + 1) / 2);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
#endif
}
