#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"
namespace Solve
{
	const int VTX_MAX = 100000,
		  EDGE_MAX = 400000;
	struct Edge
	{
		int vtx;
		bool isBridge;
		Edge *next, *inverse;
	};
	Edge edge[EDGE_MAX], edge_cp[EDGE_MAX], *begin[VTX_MAX], *prev[VTX_MAX];
	int parent[VTX_MAX], dfn[VTX_MAX], low[VTX_MAX], belong[VTX_MAX];
	bool vis[VTX_MAX];
	int nVtx, nEdge, nBridge, nBCC;

	Edge *makeEdge(int u, int v);
	void addEdge(int u, int v);

	void findBridge(int u);
	void dfs(int u, int p);
	void buildTree(int u);
	void LCA(int u, int v);

	void solve(FILE *fin, FILE *fout);
	void work(FILE *fin, FILE *fout, int n, int m);
}

Solve::Edge *Solve::makeEdge(int u, int v)
{
	Edge *e = &edge[nEdge ++];
	e->vtx = v, e->next = begin[u], e->isBridge = false, begin[u] = e;
	return e;
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
	dfn[u] = low[u] = idx ++;
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! vis[v])
		{
			parent[v] = u;
			findBridge(v);
			low[u] = MIN(low[u], low[v]);
		}
		else if(dfn[v] < dfn[u] && parent[u] != v)
			low[u] = MIN(low[u], dfn[v]);
		if(dfn[u] < low[v])
			e->isBridge = e->inverse->isBridge = true;
	}
}

void Solve::dfs(int u, int p)
{
	vis[u] = true;
	belong[u] = p;
	for(Edge *e = begin[u]; e; e = e->next)
		if(! e->isBridge)
		{
			int v = e->vtx;
			if(! vis[v])
				dfs(v, p);
		}
}

void Solve::LCA(int u, int v)
{
	static Edge *stack[VTX_MAX];
	memset(vis, 0, sizeof(bool) * nVtx);
	int top = 0;
	vis[u] = true;
	while(prev[u])
	{
		stack[top ++] = prev[u];
		u = prev[u]->inverse->vtx;
		vis[u] = true;
	}
	while(! vis[v])
	{
		if(prev[v]->isBridge)
		{
			prev[v]->isBridge = prev[v]->inverse->isBridge = false;
			nBridge --;
		}
		v = prev[v]->inverse->vtx;
	}
	for(int i = 0; i < top; i ++)
	{
		if(stack[i]->vtx == v)
			break;
		if(stack[i]->isBridge)
		{
			stack[i]->isBridge = stack[i]->inverse->isBridge = false;
			nBridge --;
		}
	}
}

void Solve::buildTree(int u)
{
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! vis[v])
		{
			prev[v] = e;
			buildTree(v);
		}
	}
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int nCase = 0;
	while(1)
	{
		int n, m;
		fscanf(fin, "%d%d", &n, &m);
		if(n == 0)
			break;
		else
		{
			nCase ++;
			fprintf(fout, "Case %d:\n", nCase);
			work(fin, fout, n, m);
			fprintf(fout, "\n");
		}
	}
}

void Solve::work(FILE *fin, FILE *fout, int n, int m)
{
	nVtx = n, nEdge = 0;
	memset(begin, 0, sizeof(Edge *) * nVtx);
	while(m --)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		addEdge(u - 1, v - 1);
	}
	memset(vis, 0, sizeof(bool) * nVtx);
	memset(dfn, 0, sizeof(int) * nVtx);
	memset(low, 0, sizeof(int) * nVtx);
	for(int u = 0; u < nVtx; u ++)
		if(! vis[u])
			findBridge(u);
	memset(vis, 0, sizeof(bool) * nVtx);
	//memset(belong, 0, sizeof(int) * nVtx);
	nBCC = 0;
	for(int u = 0; u < nVtx; u ++)
		if(! vis[u])
			dfs(u, nBCC ++);
	int nEdge_cp = nEdge;
	nEdge = 0, nVtx = nBCC;
	memcpy(edge_cp, edge, sizeof(Edge) * nEdge_cp);
	memset(begin, 0, sizeof(Edge *) * nVtx);
	for(int i = 0; i < nEdge_cp; i += 2)
	{
		int u = edge_cp[i].inverse->vtx,
			v = edge_cp[i].vtx;
		if(belong[u] == belong[v])
			continue;
		addEdge(belong[u], belong[v]);
	}
	for(int i = 0; i < nEdge; i ++)
		edge[i].isBridge = true;
	nBridge = nBCC - 1;
	memset(vis, 0, sizeof(bool) * nVtx);
	memset(prev, 0, sizeof(Edge *) * nVtx);
	buildTree(0);
	int k;
	fscanf(fin, "%d", &k);
	while(k --)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		LCA(belong[u - 1], belong[v - 1]);
		fprintf(fout, "%d\n", nBridge);
	}
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
