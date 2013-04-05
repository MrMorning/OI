#include <cstdio>
#include <cstring>
#include <iostream>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	typedef long long Val_t;
	const int VTX_MAX = 100000,
		  EDGE_MAX = 1000000;
	const Val_t INFINITY = 3000000000;
	struct Edge
	{
		int vtx;
		Edge *next;
	};
	Edge edge[EDGE_MAX], *begin[VTX_MAX];
	int profit[VTX_MAX], inDgr[VTX_MAX], outDgr[VTX_MAX];
	Val_t f[VTX_MAX];
	int nVtx, nEdge;
	void addEdge(int u, int v);
	Val_t dfs(int u);
	void solve(FILE *, FILE *);
}

void Solve::addEdge(int u, int v)
{
	Edge *e = &edge[nEdge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}

Solve::Val_t Solve::dfs(int u)
{
	if(f[u] != -INFINITY)
		return f[u];
	else if(outDgr[u] == 0)
		return f[u] = profit[u];
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		f[u] = MAX(f[u], dfs(v) + profit[u]);
	}
	return f[u];
}

void Solve::solve(FILE *fin, FILE *fout)
{
	while(! feof(fin))
	{
		int m;
		fscanf(fin, "%d %d\n", &nVtx, &m);
		nEdge = 0;
		memset(begin, 0, sizeof(Edge*) * nVtx);
		for(int u = 0; u < nVtx; u ++)
			fscanf(fin, "%d\n", &profit[u]);
		memset(inDgr, 0, sizeof(int) * nVtx);
		memset(outDgr, 0, sizeof(int) * nVtx);
		while(m --)
		{
			int u, v;
			fscanf(fin, "%d %d\n", &u, &v);
			u --, v --;
			inDgr[v] ++, outDgr[u] ++;
			addEdge(u, v);
		}
		Val_t ans = - INFINITY;
		for(int u = 0; u < nVtx; u ++)
			f[u] = - INFINITY;
		for(int u = 0; u < nVtx; u ++)
			if(inDgr[u] == 0)
				ans = MAX(ans, dfs(u));
		std::cout<< ans << '\n';
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
