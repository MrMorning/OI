/*
 * $Date:	Sun Feb 27 20:40:37 CST 2011
 * $Author:	csimstu
 * $Prob:	poj1659(根据度序列构造无向图)
 * $Sol:	Havel Theorem + Greed construction
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	const int N_VTX_MAX = 10;
	class Vertex
	{
		public:
			int idx, dgr;
			Vertex(){};
			Vertex(int _idx, int _dgr): idx(_idx), dgr(_dgr){};
	};
	struct cmp
	{
		bool operator() (const Vertex &u, const Vertex &v)
		{
			return u.dgr < v.dgr;
		}
	};
	int nVtx;
	bool linked[N_VTX_MAX][N_VTX_MAX];

	void solve(FILE *, FILE *);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int nTest;
	fscanf(fin, "%d", &nTest);
	while(nTest --)
	{
		memset(linked, 0, sizeof(linked));
		fscanf(fin, "%d", &nVtx);
		std::priority_queue<Vertex, std::vector<Vertex>, cmp> queue;
		for(int i = 0, t; i < nVtx; i ++)
		{
			fscanf(fin, "%d", &t);
			queue.push(Vertex(i, t));
		}
		bool failed = false;
		while(! queue.empty())
		{
			Vertex u = queue.top(); queue.pop();
			if(u.dgr < 0 || u.dgr > queue.size())
			{
				failed = true;
				break;
			}
			else 
			{
				static Vertex vtx[N_VTX_MAX];
				for(int i = 0; i < u.dgr; i ++)
					vtx[i] = queue.top(), queue.pop();
				for(int i = 0; i < u.dgr; i ++)
				{
					Vertex v = vtx[i];
					linked[u.idx][v.idx] = linked[v.idx][u.idx] = true;
					v.dgr --;
					queue.push(v);
				}
			}
		}
		if(failed)
			fprintf(fout, "NO\n");
		else
		{
			fprintf(fout, "YES\n");
			for(int u = 0; u < nVtx; u ++)
			{
				for(int v = 0; v < nVtx - 1; v ++)
					fprintf(fout, "%d ", linked[u][v]);
				fprintf(fout, "%d\n", linked[u][nVtx - 1]);
			}
		}
		fprintf(fout, "\n");
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
