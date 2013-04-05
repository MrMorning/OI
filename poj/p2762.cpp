#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	const int N_VTX_MAX = 1000,
		  N_EDGE_MAX = 6000;
	struct Edge
	{
		int vtx;
		Edge *next;
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
	int nEdge, nVtx, nSCC, dfn[N_VTX_MAX], lowlink[N_VTX_MAX];
	int belong[N_VTX_MAX], inDgr[N_VTX_MAX];
	bool vis[N_VTX_MAX], linked[N_VTX_MAX][N_VTX_MAX];
	bool inStack[N_VTX_MAX];

	void addEdge(int u, int v);
	void tarjan(int u);
	void dfs(int u);
	void solve(FILE *fin, FILE *fout);
	void work(FILE *fin, FILE *fout);
}

void Solve::addEdge(int u, int v)
{
	edge[nEdge].vtx = v, edge[nEdge].next = begin[u];
	begin[u] = &edge[nEdge];
	nEdge ++;
}

void Solve::tarjan(int u)
{
	static int idx = 0;
	static int stack[N_VTX_MAX];
	static int top = 0;
	dfn[u] = lowlink[u] = idx ++;
	stack[top ++] = u;
	inStack[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! dfn[v])
		{
			tarjan(v);
			lowlink[u] = MIN(lowlink[u], lowlink[v]);
		}
		else if(inStack[v])
			lowlink[u] = MIN(lowlink[u], dfn[v]);
	}
	if(lowlink[u] == dfn[u])
	{
		do
			belong[stack[top - 1]] = nSCC, inStack[stack[top - 1]] = false;
		while(stack[-- top] != u);
		nSCC ++;
	}
}

void Solve::dfs(int u)
{
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		dfs(v);
		break;
	}
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int nTest;
	fscanf(fin, "%d", &nTest);
	while(nTest --)
		work(fin, fout);
}

void Solve::work(FILE *fin, FILE *fout)
{
	int m;
	fscanf(fin, "%d%d", &nVtx, &m);
	nEdge = 0;
	memset(begin, 0, sizeof(Edge *) * nVtx);
	memset(dfn, 0, sizeof(int) * nVtx);
	memset(lowlink, 0, sizeof(int) * nVtx);
	memset(belong, 0, sizeof(int) * nVtx);
	nSCC = 0;
	while(m --)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		addEdge(u - 1, v - 1);
	}
	memset(inStack, 0, sizeof(nVtx));
	for(int u = 0; u < nVtx; u ++)
		if(! dfn[u])
			tarjan(u);
	memset(linked, 0, sizeof(linked));
	for(int u = 0; u < nVtx; u ++)
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			if(belong[u] != belong[v])
				 linked[belong[u]][belong[v]] = true;
		}
	nEdge = 0;
	memset(begin, 0, sizeof(Edge *) * nSCC);
	memset(inDgr, 0, sizeof(int) * nSCC);
	for(int u = 0; u < nSCC; u ++)
		for(int v = 0; v < nSCC; v ++)
			if(linked[u][v])
				addEdge(u, v), inDgr[v] ++;
	memset(vis, 0, sizeof(bool) * nSCC);
	int u;
	for(u = 0; u < nVtx; u ++)
		if(inDgr[u] == 0)
			break;
	dfs(u);
	bool failed = false;
	for(int v = 0; v < nSCC; v ++)
		if(! vis[v])
		{
			failed = true;
			break;
		}
	if(failed)
		fprintf(fout, "NO\n");
	else
		fprintf(fout, "YES\n");
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
