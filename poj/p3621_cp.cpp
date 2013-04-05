/*
 * $Date: 	Sun Feb 27 19:31:51 CST 2011
 * $Author: csimstu
 * $Prob:	poj3621(求最大比例环分数规划)
 * $Sol:	二分+spfa判负环
 */
#include <cstdio>
#include <cstring>
#define INPUT "t.in"
#define OUTPUT "t.out"
namespace Solve
{
	typedef double Val_d;
#define INF_D 1E8
	const int N_VTX_MAX = 1000, N_EDGE_MAX = 5000;
	const double EPS = 10E-5;
	class Edge
	{
		public:
			int vtx;
			Val_d dist;
			Edge *next;
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
	int weight[N_VTX_MAX], nVtx, nEdge;

	void addEdge(int u, int v, Val_d dist);
	bool spfa(int sVtx);
	void solve(FILE *fin, FILE *fout);
}

namespace SaveAndLoad
{
	Solve::Val_d dist[Solve::N_EDGE_MAX];
	void save()
	{
		for(int i = 0; i < Solve::nEdge; i ++)
			dist[i] = Solve::edge[i].dist;
	}
	void load()
	{
		for(int i = 0; i < Solve::nEdge; i ++)
			Solve::edge[i].dist = dist[i];
	}
}

void Solve::addEdge(int u, int v, Val_d dist)
{
	edge[nEdge].vtx = v;
	edge[nEdge].dist = dist;
	edge[nEdge].next = begin[u];
	begin[u] = &edge[nEdge];
	nEdge ++;
}

bool Solve::spfa(int sVtx)//存在负环:false
{
	static int queue[N_VTX_MAX];
	static bool inQueue[N_VTX_MAX];
	static int times[N_VTX_MAX];
	static Val_d dist[N_VTX_MAX];
	memset(inQueue, 0, sizeof(bool) * nVtx);
	memset(times, 0, sizeof(int) * nVtx);
	for(int u = 0; u < nVtx; u ++)
		dist[u] = INF_D;
	dist[sVtx] = 0;
	queue[0] = sVtx;
	inQueue[sVtx] = true;
	times[sVtx] = 1;
	for(int head = 0, tail = 1; head != tail; head = (head + 1) % nVtx)
	{
		int u = queue[head];
		inQueue[u] = false;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			Val_d tmp = dist[u] + e->dist;
			if(tmp < dist[v])
			{
				dist[v] = tmp;
				if(! inQueue[v])
				{
					if(times[v] > nVtx)
						return false;
					queue[tail] = v;
					tail = (tail + 1) % nVtx;
					inQueue[v] = true;
					times[v] ++;
				}
			}
		}
	}
	return true;
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int m;
	fscanf(fin, "%d%d", &nVtx, &m);
	for(int u = 0; u < nVtx; u ++)
		fscanf(fin, "%d", &weight[u]);
	while(m --)
	{
		int a, b, c;
		fscanf(fin, "%d%d%d", &a, &b, &c);
		a --, b --;
		addEdge(a, b, c);
	}
	spfa(0);
	SaveAndLoad::save();
	double l = 0, r = 10E6, mid = (l + r) / 2;
	while(r - l > EPS)
	{
		SaveAndLoad::load();
		for(int i = 0; i < nEdge; i ++)
			edge[i].dist = edge[i].dist * mid - weight[edge[i].vtx];
		if(spfa(0))
			r = mid;
		else
			l = mid;
		mid = (l + r) / 2;
	}
	fprintf(fout, "%.2f\n", mid);
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
