#include <cstdio>
#include <cstring>
#include <queue>
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	const int VTX_MAX = 200,
		  EDGE_MAX = VTX_MAX * VTX_MAX;
	struct Edge
	{
		int vtx;
		Edge *next;
	} edge[EDGE_MAX], *begin[VTX_MAX];
	int nVtx, nEdge, inDgr[VTX_MAX], nSeq, seq[VTX_MAX], ans[VTX_MAX];
	bool used[VTX_MAX];
	void addEdge(int u, int v);
	void topsort();
	void solve(FILE *fin, FILE *fout);
	void work(FILE *fin, FILE *fout);
}

void Solve::addEdge(int u, int v)
{
	Edge *e = &edge[nEdge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
	inDgr[v] ++;
}

void Solve::topsort()
{
	std::priority_queue<int> queue;
	memset(used, 0, sizeof(bool) * nVtx);
	nSeq = 0;
	for(int u = 0; u < nVtx; u ++)
		if(inDgr[u] == 0)
			queue.push(u), used[u] = true;
	while(! queue.empty())
	{
		int u = queue.top(); queue.pop();
		seq[nSeq ++] = u;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			if(! used[v])
			{
				inDgr[v] --;
				if(inDgr[v] == 0)
					queue.push(v), used[v] = true;
			}
		}
	}
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int nTestCases;
	fscanf(fin, "%d", &nTestCases);
	while(nTestCases --)
		work(fin, fout);
}

void Solve::work(FILE *fin, FILE *fout)
{
	int m;
	nEdge = 0;
	memset(begin, 0, sizeof(Edge *) * nVtx);
	fscanf(fin, "%d%d", &nVtx, &m);
	memset(inDgr, 0, sizeof(int) * nVtx);
	while(m --)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		addEdge(v - 1, u - 1);
	}
	topsort();
	if(nSeq < nVtx)
		fprintf(fout, "-1\n");
	else
	{
		for(int i = nSeq - 1; i >= 0; i --)
			ans[seq[i]] = nSeq - 1 - i;
		for(int i = 0; i < nSeq - 1; i ++)
			fprintf(fout, "%d ", ans[i] + 1);
		fprintf(fout, "%d\n", ans[nSeq - 1] + 1);
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
