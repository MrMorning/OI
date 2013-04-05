#include <cstdio>
#include <cstring>
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	const int N_VTX_MAX = 100,
		  N_EDGE_MAX = 600;
#define DIST_INF 0x3f3f3f3f
	const int COST_MAX = 10000;
	class Edge
	{
		public:
			int t, dist, cost;
			Edge *next;
	};
	class State
	{
		public:
			int idx, cost, dist;
			State(){};
			State(int _idx, int _cost, int _dist): idx(_idx), cost(_cost), dist(_dist){};
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
	int nEdge, nVtx, sVtx, tVtx;
	int dist[N_VTX_MAX][COST_MAX];

	void addEdge(int u, int v, int dist, int cost);
	void spfa();
	void solve(FILE*, FILE*);
}

void Solve::addEdge(int u, int v, int cost, int dist)
{
	Edge *e = &edge[nEdge];
	e->t = v, e->dist = dist, e->cost = cost;
	e->next = begin[u];
	begin[u] = e;
	nEdge ++;
}

void Solve::spfa()
{
	static State queue[N_VTX_MAX * COST_MAX];
	static bool inQueue[N_VTX_MAX][COST_MAX];
	memset(dist, 0x3f, sizeof(dist));
	memset(inQueue, 0, sizeof(inQueue));
	inQueue[sVtx][0] = true;
	dist[sVtx][0] = 0;
	queue[0] = State(sVtx, 0, 0);
	for(int q_h = 0, q_t = 1; q_h != q_t; q_h = (q_h + 1) % (N_VTX_MAX * COST_MAX))
	{
		State u = queue[q_h];
		inQueue[u.idx][u.cost] = false;
		for(Edge *e = begin[u.idx]; e; e = e->next)
		{
			int v = e->t;
			int tmp = e->dist + dist[u.idx][u.cost];
			if(u.cost + e->cost < COST_MAX && tmp < dist[v][u.cost + e->cost])
			{
				dist[v][u.cost + e->cost] = tmp;
				if(! inQueue[v][u.cost + e->cost])
				{
					queue[q_t] = State(v, u.cost + e->cost, tmp);
					q_t = (q_t + 1) % (N_VTX_MAX * COST_MAX);
					inQueue[v][u.cost + e->cost] = true;
				}
			}
		}
	}
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int m;
	fscanf(fin, "%d%d%d%d", &nVtx, &m, &sVtx, &tVtx);
	sVtx --, tVtx --;
	while(m --)
	{
		int u, v, t1, t2;
		fscanf(fin, "%d%d%d%d", &u, &v, &t1, &t2);
		u --, v --;
		addEdge(u, v, t1, t2);
		addEdge(v, u, t1, t2);
	}
	spfa();
	int minDist = DIST_INF, ans = 0;
	for(int i = 0; i < COST_MAX; i ++)
		if(dist[tVtx][i] < minDist)
		{	
			//fprintf(fout, "%d %d\n", i, dist[tVtx][i]);
			minDist = dist[tVtx][i];
			ans ++;
		}
	fprintf(fout, "%d\n", ans);

}

int main()
{
//#ifdef STDIO
//	Solve::solve(stdin, stdout);
//#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, stdout);
//#endif
}
