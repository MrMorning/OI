#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	typedef int Flow_t;
#define FLOW_INF 0x3f3f3f3f
	const int N_VTX_MAX = 200 + 2,
		  N_EDGE_MAX = 2 * (5000 + 100 * 2);
	struct Edge
	{
		int vtx;
		Flow_t cap;
		Edge *next, *inverse;
	};
	struct Answer
	{
		int idx, flag;
		Answer(){};
		Answer(int _idx, int _flag): idx(_idx), flag(_flag){};
	} ans[N_VTX_MAX];
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
	int nEdge, nVtx, level[N_VTX_MAX];
	bool vis[N_VTX_MAX];

	Edge *makeEdge(int u, int v, Flow_t cap);
	void addEdge(int u, int v, Flow_t cap);

	bool preLabel(int sVtx, int tVtx);
	Flow_t findAug(int u, int tVtx, Flow_t flow);
	Flow_t dinic(int sVtx, int tVtx);

	void dfs(int u);

	void solve(FILE *fin, FILE *fout);
}

Solve::Edge *Solve::makeEdge(int u, int v, Flow_t cap)
{
	Edge *e = &edge[nEdge ++];
	e->vtx = v, e->next = begin[u], e->cap = cap;
	return begin[u] = e;
}

void Solve::addEdge(int u, int v, Flow_t cap)
{
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->inverse = e2, e2->inverse = e1;
}

bool Solve::preLabel(int sVtx, int tVtx)
{
	static int queue[N_VTX_MAX];
	memset(level, -1, sizeof(int) * nVtx);
	queue[0] = sVtx, level[sVtx] = 0;
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

Solve::Flow_t Solve::findAug(int u, int tVtx, Flow_t flow)
{
	if(u == tVtx)
		return flow;
	for(Edge *e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(level[v] == level[u] + 1)
				if(Flow_t tmp = findAug(v, tVtx, MIN(flow, e->cap)))
				{
					e->cap -= tmp;
					e->inverse->cap += tmp;
					cur[u] = e;
					return tmp;
				}
		}
	return 0;
}

Solve::Flow_t Solve::dinic(int sVtx, int tVtx)
{
	Flow_t maxflow = 0;
	while(preLabel(sVtx, tVtx))
	{
		memcpy(cur, begin, sizeof(Edge*) * nVtx);
		while(Flow_t tmp = findAug(sVtx, tVtx, FLOW_INF))
			maxflow += tmp;
	}
	return maxflow;
}

void Solve::dfs(int u)
{
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(! vis[v])
				dfs(v);
		}
}

void Solve::solve(FILE *fin, FILE *fout)
{
#define LVTX(x) ((x)*2)
#define RVTX(x) ((x)*2+1)
	int n, m;
	fscanf(fin, "%d%d", &n, &m);
	nVtx = n * 2 + 2;
	int sVtx = nVtx - 2, tVtx = nVtx - 1;
	for(int u = 0, t; u < n; u ++)
	{
		fscanf(fin, "%d", &t);
		addEdge(RVTX(u), tVtx, t);
	}
	for(int u = 0, t; u < n; u ++)
	{
		fscanf(fin, "%d", &t);
		addEdge(sVtx, LVTX(u), t);
	}
	while(m --)
	{
		int u, v;
		fscanf(fin, "%d%d", &u, &v);
		addEdge(LVTX(u - 1), RVTX(v - 1), FLOW_INF);
	}
	fprintf(fout, "%d\n", dinic(sVtx, tVtx));
	dfs(sVtx);
	int nAns = 0;
	for(Edge *e = begin[sVtx]; e; e = e->next)
		if(! vis[e->vtx])
			ans[nAns ++] = Answer(e->vtx / 2 + 1, -1);
	for(Edge *e = begin[tVtx]; e; e = e->next)
		if(vis[e->vtx])
			ans[nAns ++] = Answer((e->vtx - 1) / 2 + 1, 1);
	fprintf(fout, "%d\n", nAns);
	for(int i = 0; i < nAns; i ++)
		if(ans[i].flag == 1)
			fprintf(fout, "%d +\n", ans[i].idx);
		else
			fprintf(fout, "%d -\n", ans[i].idx);
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
