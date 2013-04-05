#include <cstdio>
#include <cstring>
#define INPUT "t.in"
#define OUTPUT "t.out"
#define MIN(a,b) ((a)<(b)?(a):(b))

namespace Solve
{
	const int VTX_MAX = 1000, EDGE_MAX = 1000000;
	struct Edge
	{
		int vtx;
		Edge *next, *inverse;
	};
	Edge edge[EDGE_MAX], *begin[VTX_MAX];
	int nEdge, nVtx, nBCC, nowBCC;
	bool linked[VTX_MAX][VTX_MAX], belong[VTX_MAX][VTX_MAX], vis[VTX_MAX];
	int dfn[VTX_MAX], low[VTX_MAX], color[VTX_MAX];
	int idx, top, stack[VTX_MAX];
	bool fail[VTX_MAX];

	Edge *makeEdge(int u, int v);
	void addEdge(int u, int v);

	void findBlock(int u, int v);
	bool dfs(int u, int c);
	void solve(FILE *fin, FILE *fout);
	void work(int m, FILE *fin, FILE *fout);
}

Solve::Edge *Solve::makeEdge(int u, int v)
{
	Edge *e = &edge[nEdge ++];
	e->vtx = v; e->next = begin[u], begin[u] = e;
	return e;
}

void Solve::addEdge(int u, int v)
{
	Edge *e1 = makeEdge(u, v),
		 *e2 = makeEdge(v, u);
	e1->inverse = e2, e2->inverse = e1;
}

void Solve::findBlock(int u, int f)
{
	vis[u] = true;
	stack[top ++] = u;
	dfn[u] = low[u] = idx ++;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(! vis[v])
		{
			findBlock(v, u);
			if(dfn[u] <= low[v])
			{
				int tmp;
				do
				{
					tmp = stack[-- top];
					belong[tmp][nBCC] = true;
				}
				while(tmp != v);
				belong[u][nBCC ++] = true;
			}
			low[u] = MIN(low[u], low[v]);
		}
		else if(v != f)
			low[u] = MIN(low[u], dfn[v]);
	}
}

bool Solve::dfs(int u, int c)
{
	if(color[u] == -1)
		color[u] = c;
	else
		return color[u] ^ c;
	for(Edge *e = begin[u]; e; e = e->next)
		if(belong[e->vtx][nowBCC])
			if(dfs(e->vtx, ! c))
				return true;
	return false;
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int m;
	while(1)
	{
		fscanf(fin, "%d%d", &nVtx, &m);
		if(nVtx == 0 && m == 0)
			break;
		work(m, fin, fout);
	}
}

void Solve::work(int m, FILE *fin, FILE *fout)
{
	memset(linked, 0, sizeof(linked));
	while(m --)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		u --, v --;
		linked[u][v] = linked[v][u] = true;
	}
	nEdge = 0;
	memset(begin, 0, sizeof(Edge *) * nVtx);
	for(int u = 0; u < nVtx; u ++)
		for(int v = u + 1; v < nVtx; v ++)
			if(! linked[u][v])
				addEdge(u, v);
	memset(vis, 0, sizeof(bool) * nVtx);
	memset(dfn, -1, sizeof(int) * nVtx);
	memset(belong, 0, sizeof(belong));
	nBCC = 0;
	for(int u = 0; u < nVtx; u ++)
		if(! vis[u])
		{
			top = idx = 0;
			findBlock(u, -1);
		}
	memset(fail, 1, sizeof(bool) * nVtx);
	for(nowBCC = 0; nowBCC < nBCC; nowBCC ++)
		for(int u = 0; u < nVtx; u ++)
			if(belong[u][nowBCC])
			{
				memset(color, -1, sizeof(int) * nVtx);
				if(dfs(u, 0))
					for(int v = 0; v < nVtx; v ++)
						if(belong[v][nowBCC])
							fail[v] = false;
				break;
			}
	int ans = 0;
	for(int u = 0; u < nVtx; u ++)
		if(fail[u])
			ans ++;
	fprintf(fout, "%d\n", ans);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, stdout);
#endif
}
