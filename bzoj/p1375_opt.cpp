#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
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
	struct cmp
	{
		bool operator()(const State &u, const State &v)
		{
			return u.dist > v.dist;
		}
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
	int nEdge, nVtx, sVtx, tVtx;
	int dist[N_VTX_MAX][COST_MAX];

	void addEdge(int u, int v, int dist, int cost);
	void spfa();
	int dijkstra();
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

int Solve::dijkstra()
{
	std::priority_queue<State, std::vector<State>, cmp> queue;
	static int minCost[N_VTX_MAX],
			   minDist[N_VTX_MAX];
	memset(minCost, 0x3f, sizeof(minCost));
	minCost[sVtx] = 0;
	memset(minDist, 0x3f, sizeof(minDist));
	minDist[sVtx] = 0;
	queue.push(State(sVtx, 0, 0));
	int ans = 0;
	while(queue.size())
	{
		State u = queue.top(); queue.pop();
		if(u.idx == tVtx && u.cost == 124 && u.dist == 337)
			printf("!! %d %d\n", minCost[u.idx], minDist[u.idx]);
		if((u.dist >= minDist[u.idx] && u.cost > minCost[u.idx]) || (u.dist > minDist[u.idx] && u.cost >= minCost[u.idx]))
			continue;
		if(u.idx == tVtx)
		{
	//		printf("%d %d\n", u.cost, u.dist);
			ans ++;
		}
		for(Edge *e = begin[u.idx]; e; e = e -> next)
		{
			int v = e -> t;
			int tmpDist = u.dist + e -> dist;
			int tmpCost = u.cost + e -> cost;
			if(tmpDist < minDist[v] || tmpCost < minCost[v])
			{
				if(tmpDist <= minDist[v] && tmpCost <= minCost[v])
					minDist[v] = tmpDist, minCost[v] = tmpCost;
				queue.push(State(v, tmpCost, tmpDist));
			}
		}
	}
	return ans;
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
	/*spfa();
	int minDist = DIST_INF, ans = 0;
	for(int i = 0; i < COST_MAX; i ++)
		if(dist[tVtx][i] < minDist)
		{	
			//fprintf(fout, "%d %d\n", i, dist[tVtx][i]);
			minDist = dist[tVtx][i];
			ans ++;
		}
	fprintf(fout, "%d\n", ans);*/
	fprintf(fout, "%d\n", dijkstra());
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
