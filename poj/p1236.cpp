/*
 * $Date:	Sun Feb 27 14:21:02 CST 2011
 * $Author: csimstu
 * $Prob:	poj1236
 * $Sol:	tarjan SCC
 */
#include <cstdio>
#include <cstring>
#define INPUT "schlnet.in"
#define OUTPUT "schlnet.out"
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

namespace Solve
{
	const int N_VTX_MAX = 100;
#define SQR(x) ((x)*(x))
	const int N_EDGE_MAX = SQR(N_VTX_MAX);
#undef SQR
	class Edge
	{
		public:
			int vtx;
			Edge *next;
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
	int nVtx, nEdge;
	int nSCC, dfn[N_VTX_MAX], lowlink[N_VTX_MAX], stack[N_VTX_MAX], belong[N_VTX_MAX];
	int inDegree[N_VTX_MAX], outDegree[N_VTX_MAX];
	bool vis[N_VTX_MAX], inStack[N_VTX_MAX];

	void addEdge(int u, int v);

	void tarjan(int u);
	void solve(FILE*, FILE*);
}
void Solve::addEdge(int u, int v)
{
	edge[nEdge].vtx = v;
	edge[nEdge].next = begin[u];
	begin[u] = &edge[nEdge];
	nEdge ++;
}
void Solve::tarjan(int u)
{
	vis[u] = true;
	int	static index = 0;
	int	static top = 0;
	dfn[u] = lowlink[u] = index ++;
	stack[top ++] = u;
	inStack[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! vis[v])
			tarjan(v), lowlink[u] = MIN(lowlink[u], lowlink[v]);
		else if(inStack[v])
			lowlink[u] = MIN(lowlink[u], dfn[v]);
	}
	if(lowlink[u] == dfn[u])
	{
		do
		{
			belong[stack[-- top]] = nSCC;
			inStack[stack[top]] = false;
		}
		while(stack[top] != u);
		nSCC ++;
	}
}
void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d", &nVtx);
	for(int u = 0, v; u < nVtx; u ++)
	{
		while(true)
		{
			fscanf(fin, "%d", &v);
			if(v == 0)
				break;
			addEdge(u, v - 1);
		}
	}
	memset(vis, 0, sizeof(bool) * nVtx);
	for(int u = 0; u < nVtx; u ++)
		if(! vis[u])
			tarjan(u);
	for(int u = 0; u < nVtx; u ++)
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			if(belong[u] != belong[v])
				outDegree[belong[u]] ++, inDegree[belong[v]] ++;
		}
	int zeroInDgrCnt = 0, zeroOutDgrCnt = 0;
	for(int u = 0; u < nSCC; u ++)
	{
		if(inDegree[u] == 0)
			zeroInDgrCnt ++;
		if(outDegree[u] == 0)
			zeroOutDgrCnt ++;
	}
	fprintf(fout, "%d\n", zeroInDgrCnt);
	if(nSCC == 1)
		fprintf(fout, "0\n");
	else
		fprintf(fout, "%d\n", MAX(zeroInDgrCnt, zeroOutDgrCnt));
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
