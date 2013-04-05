#include <cstdio>
#include <cstring>
#include <algorithm>

namespace Solve
{
	typedef long long Val_t;
#define VAL_T_FMT "%lld"
	const int VTX_MAX = 100000,
		  EDGE_MAX = 200000,
		  QUERY_MAX = 200000;
	struct Query
	{
		int idx, val;
		bool operator< (const Query &x) const
		{
			return val < x.val;
		}
	} query[QUERY_MAX];
	struct Edge
	{
		int u, v, w;
		bool operator< (const Edge &x) const
		{
			return w < x.w;
		}
	} edge[EDGE_MAX];
	int rank[VTX_MAX], parent[VTX_MAX];
	Val_t cnt[VTX_MAX];
	Val_t ans[QUERY_MAX];
	int nVtx, nEdge, nQuery;

	void mkset(int u);
	int findset(int u);
	void mergeset(int u, int v);

	void solve(FILE *fin, FILE *fout);
}

void Solve::mkset(int u)
{
	parent[u] = u;
	rank[u] = 0;
	cnt[u] = 1;
}

int Solve::findset(int u)
{
	if(parent[u] != u)
		parent[u] = findset(parent[u]);
	return parent[u];
}

void Solve::mergeset(int u, int v)
{
	if(rank[u] > rank[v])
	{
		parent[v] = u;
		cnt[u] += cnt[v];
		cnt[v] = 0;
	}
	else
	{
		parent[u] = v;
		cnt[v] += cnt[u];
		cnt[u] = 0;
		if(rank[u] == rank[v])
			rank[v] ++;
	}
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d%d%d", &nVtx, &nEdge, &nQuery);
	for(int i = 0; i < nVtx; i ++)
		mkset(i);
	for(int i = 0; i < nEdge; i ++)
		fscanf(fin, "%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
	std::sort(edge, edge + nEdge);
	for(int i = 0; i < nQuery; i ++)
	{
		query[i].idx = i;
		fscanf(fin, "%d", &query[i].val);
	}
	std::sort(query, query + nQuery);
	int edgeIt = 0;
	Val_t ansCnt = 0;
	for(int i = 0; i < nQuery; i ++)
	{
		while(edgeIt < nEdge && edge[edgeIt].w <= query[i].val)
		{
			int u = edge[edgeIt].u - 1, v = edge[edgeIt].v - 1;
			int p = findset(u);
			int q = findset(v);
			if(p != q)
			{
				ansCnt += cnt[p] * cnt[q];
				mergeset(p, q);
			}
			edgeIt ++;
		}
		ans[query[i].idx] = ansCnt;
	}
	for(int i = 0; i < nQuery; i ++)
		fprintf(fout, VAL_T_FMT "\n", ans[i]);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen("t.in", "r"),
		 *fout = fopen("t.out", "w");
	Solve::solve(fin, fout);
#endif
}
