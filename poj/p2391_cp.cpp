/*
 * $Date: Sat Feb 26 22:52:41 CST 2011
 * $Author: csimstu
 * $Prob: poj2391
 * $Sol: floyd + dinic
 */
#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"
#define INT64_MAX 1152921504606846976
#define ST(x) ((x)*2)
#define EN(x) ((x)*2+1)
//#define STDIO

namespace Solve
{
	typedef long long Val_d; // for dist
	typedef int Val_f; // for flow
	const Val_d INF_D = INT64_MAX;
#define VAL_D_FMT "%lld"
	const Val_f INF_F = 1 << 29;
	const int N_VTX_MAX = 200 * 2 + 2;
	const int N_EDGE_MAX = 2 * (200 * 2 + 200 * 200);
	class Edge
	{
		public:
			int vtx;
			Val_f cap;
			Edge *next, *inverse;
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
	Val_d dist[N_VTX_MAX][N_VTX_MAX];
	int level[N_VTX_MAX], nCow, nEdge, nVtx, sVtx, tVtx;
	int checked[N_EDGE_MAX];

	Edge* addEdge(int u, int v, Val_f cap);
	Edge* makeEdge(int u, int v, Val_f cap);

	void saveCap();
	void loadCap();

	void floyd();
	Val_f dinic(int sVtx, int tVtx);
	Val_f findAug(int u, int tVtx, Val_f flow);
	bool preLabel(int sVtx, int tVtx);

	bool check(Val_d time);	
	void solve(FILE *fin, FILE *fout);
	void readData(FILE *fin);
}

namespace SaveAndLoad
{
	Solve::Edge static edge_cp[Solve::N_EDGE_MAX];
	Solve::Edge static *begin_cp[Solve::N_VTX_MAX];
	int static nEdge_cp;
	void save()
	{
		nEdge_cp = Solve::nEdge;
		memcpy(edge_cp, Solve::edge, sizeof(edge_cp));
		memcpy(begin_cp, Solve::begin, sizeof(begin_cp));
	}

	void load()
	{
		Solve::nEdge = nEdge_cp;
		memcpy(Solve::edge, edge_cp, sizeof(edge_cp));
		memcpy(Solve::begin, begin_cp, sizeof(begin_cp));
	}
}

Solve::Edge* Solve::addEdge(int u, int v, Val_f cap)
{
	Edge &e_t = edge[nEdge ++];
	e_t.vtx = v, e_t.cap = cap;
	e_t.next = begin[u];
	begin[u] = &e_t;
	return &e_t;
}

Solve::Edge* Solve::makeEdge(int u, int v, Val_f cap)
{
	Edge *e1 = addEdge(u, v, cap);
	Edge *e2 = addEdge(v, u, 0);
	e1->inverse = e2, e2->inverse = e1;
	return e1;
}

void Solve::floyd()
{
	for(int k = 0; k < nVtx; k ++)
		for(int i = 0; i < nVtx; i ++)
			for(int j = 0; j < nVtx; j ++)
				dist[i][j] = MIN(dist[i][j], dist[i][k] + dist[k][j]);
}

Solve::Val_f Solve::dinic(int sVtx, int tVtx)
{
	Val_f maxFlow = 0;
	while(preLabel(sVtx, tVtx))
	{
		memcpy(cur, begin, sizeof(Edge *) * (2 * nVtx + 2));
		while(Val_f tmp = findAug(sVtx, tVtx, INF_F))
			maxFlow += tmp;
	}
	return maxFlow;
}

Solve::Val_f Solve::findAug(int u, int tVtx, Val_f flow)
{
	if(u == tVtx)
		return flow;
	for(Edge *e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(level[v] == level[u] + 1)
				if(Val_f tmp = findAug(v, tVtx, MIN(e->cap, flow)))
				{
					e->cap -= tmp;
					e->inverse->cap += tmp;
					cur[u] = e;
					return tmp;
				}
		}
	return (Val_f) 0;
}

bool Solve::preLabel(int sVtx, int tVtx)
{
	static int queue[N_VTX_MAX];
	memset(level, -1, sizeof(int) * (2 * nVtx + 2));
	level[sVtx] = 0;
	queue[0] = sVtx;
	for(int head = 0, tail = 1; head != tail; head ++)
	{
		int u = queue[head];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(level[v] == -1)
				{
					level[v] = level[u] + 1;
					if(v == tVtx)
						return true;
					queue[tail ++] = v;
				}
			}
	}
	return false;
}

bool Solve::check(Val_d time)
{
	int cnt = 0;
	for(int u = 0; u < nVtx; u ++)
		for(int v = 0; v < nVtx; v ++)
			if(dist[u][v] <= time)
				cnt ++;
	if(checked[cnt] == -1)
	{
		for(int u = 0; u < nVtx; u ++)
			for(int v = 0; v < nVtx; v ++)
				if(dist[u][v] <= time)
					makeEdge(ST(u), EN(v), INF_F);
		checked[cnt] = (dinic(sVtx, tVtx) == nCow);
	}
	return checked[cnt];
}

void Solve::solve(FILE *fin, FILE *fout)
{
	readData(fin);
	memset(checked, -1, sizeof(checked));
	floyd();
	Val_d l = 0, r = INF_D, mid = (l + r) / 2;
	while(l < r)
	{
		SaveAndLoad::load();
		if(check(mid))
			r = mid;
		else
			l = mid + 1;
		mid = (l + r) / 2;
	}
	if(mid == INF_D)
		mid = -1;
	fprintf(fout, VAL_D_FMT "\n", mid);
}

void Solve::readData(FILE *fin)
{
	int m;
	fscanf(fin, "%d%d", &nVtx, &m);
	sVtx =  2 * nVtx, tVtx = 2 * nVtx + 1;
	for(int u = 0, t1, t2; u < nVtx; u ++)
	{
		fscanf(fin, "%d%d", &t1, &t2);
		nCow += t1;
		makeEdge(sVtx, ST(u), t1);
		makeEdge(EN(u), tVtx, t2);
	}
	SaveAndLoad::save();
	for(int i = 0; i < nVtx; i ++)
		for(int j = 0; j < nVtx; j ++)
			if(i != j)
				dist[i][j] = INF_D;
	for(int i = 0, t1, t2, t3; i < m; i ++)
	{
		fscanf(fin, "%d%d%d", &t1, &t2, &t3);
		t1 --, t2 --;
		dist[t1][t2] = MIN(dist[t1][t2], t3);
		dist[t2][t1] = dist[t1][t2];
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
	fclose(fin);
	fclose(fout);
	return 0;
#endif
}
