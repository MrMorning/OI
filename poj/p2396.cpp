#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"

namespace Solve
{
	typedef int Val_f;
	const int INF_F = 1 << 29;
#define VAL_F_FMT "%d"
	const int N_VTX_MAX = 200 + 20 + 2 + 2,
		  	  N_EDGE_MAX = 3 * (200 + 20 + 200 * 20);
	class Edge
	{
		public:
			int t;
			Val_f cap, cap_cp, downlim;
			Edge *next, *inverse;
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
	Val_f downlim[200][20], uplim[200][20], ans[200][20], adjustVal[N_VTX_MAX];
	int nRow, nCol, nVtx, nEdge, sVtx_old, tVtx_old, sVtx_new, tVtx_new;
	int level[N_VTX_MAX];
	bool failed;
	Edge *makeEdge(int u, int v, Val_f cap);
	void addEdge(int u, int v, Val_f downlim, Val_f cap);
	void setEdge(int u, int v, Val_f downlim, Val_f uplim);
	void adjust();

	Val_f dinic(int sVtx, int tVtx);
	Val_f findAug(int u, int tVtx, Val_f flow);
	bool label(int sVtx, int tVtx);

	void init();
	void solve(FILE *, FILE *);
	inline void setRes(int i, int j, char ctrl, Val_f val);
	void debug()
	{
		for(int u = 0; u < nVtx; u ++)
			for(Edge *e = begin[u]; e; e = e->next)
				if(e->cap)
				printf("%d -> %d , cap: %d\n", u, e->t, e->cap);
	}
}

Solve::Edge *Solve::makeEdge(int u, int v, int cap)
{
	Edge &e_t = edge[nEdge];
	e_t.t = v, e_t.cap = cap;
	e_t.next = begin[u];
	begin[u] = &e_t;
	nEdge ++;
	return &e_t;
}

void Solve::addEdge(int u, int v, Val_f downlim, Val_f cap)
{
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->downlim = downlim, e1->cap_cp = e1->cap;
	e1->inverse = e2, e2->inverse = e1;
}
void Solve::setEdge(int u, int v, Val_f downlim, Val_f uplim)
{
//	printf("%d -> %d : [%d, %d]\n", u, v, downlim, uplim);
	adjustVal[u] -= downlim;
	adjustVal[v] += downlim;
	addEdge(u, v, downlim, uplim - downlim);
}

void Solve::adjust()
{
	for(int u = 0; u < nVtx; u ++)
		if(adjustVal[u] > 0)
			setEdge(sVtx_new, u, 0, adjustVal[u]);
		else if(adjustVal[u] < 0)
			setEdge(u, tVtx_new, 0, - adjustVal[u]);
}

Solve::Val_f Solve::dinic(int sVtx, int tVtx)
{
	Val_f maxflow = 0;
	while(label(sVtx, tVtx))
	{
		memcpy(cur, begin, sizeof(Edge*) * nVtx);
		while(Val_f tmp = findAug(sVtx, tVtx, INF_F))
			maxflow += tmp;
	}
	return maxflow;
}

bool Solve::label(int sVtx, int tVtx)
{
	static int queue[N_VTX_MAX];
	memset(level, -1, sizeof(int) * nVtx);
	queue[0] = sVtx;
	level[sVtx] = 0;
	for(int q_h = 0, q_t = 1; q_h != q_t; q_h ++)
	{
		int u = queue[q_h];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->t;
				if(e->cap && level[v] == -1)
				{
					level[v] = level[u] + 1;
					if(v == tVtx)
						return true;
					queue[q_t ++] = v;
				}
			}
	}
	return false;
}

Solve::Val_f Solve::findAug(int u, int tVtx, Val_f flow)
{
	if(u == tVtx)
		return flow;
	for(Edge *e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->t;
			if(level[v] == level[u] + 1)
				if(Val_f tmp = findAug(v, tVtx, MIN(e->cap, flow)))
				{
					e->cap -= tmp;
					e->inverse->cap += tmp;
					cur[u] = e;
					return tmp;
				}
		}
	return 0;
}

void Solve::init()
{
	failed = false;
	nEdge = 0;
	memset(begin, 0, sizeof(begin));
	memset(adjustVal, 0, sizeof(adjustVal));
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int nTest;
	fscanf(fin, "%d", &nTest);
	while(nTest --)
	{
		init();
		fscanf(fin, "%d%d", &nRow, &nCol);
		sVtx_old = nRow + nCol, tVtx_old = nRow + nCol + 1;
		sVtx_new = nRow + nCol + 2, tVtx_new = nRow + nCol + 3;
		nVtx = nRow + nCol + 4;
		for(int u = 0; u < nRow; u ++)
		{
			Val_f tmp;
			fscanf(fin, VAL_F_FMT, &tmp);
			setEdge(sVtx_old, u, tmp, tmp);
		}
		for(int u = nRow; u < nRow + nCol; u ++)
		{
			Val_f tmp;
			fscanf(fin, VAL_F_FMT, &tmp);
			setEdge(u, tVtx_old, tmp, tmp);
		}
		for(int i = 0; i < nRow; i ++)
			for(int j = 0; j < nCol; j ++)
				uplim[i][j] = INF_F, downlim[i][j] = 0;
		int t;
		fscanf(fin, "%d", &t);
		while(t --)
		{
			int i, j;
			Val_f val;
			char ctrl;
			fscanf(fin, "%d %d %c %d", &i, &j, &ctrl, &val);
			if(i == 0 && j == 0)
				for(int l = 0; l < nRow; l ++)
					for(int s = 0; s < nCol; s ++)
						setRes(l, s, ctrl, val);
			else if(i == 0)
				for(int l = 0; l < nRow; l ++)
					setRes(l, j - 1, ctrl, val);
			else if(j == 0)
				for(int s = 0; s < nCol; s ++)
					setRes(i - 1, s, ctrl, val);
			else
				setRes(i - 1, j - 1, ctrl, val);
		}
		if(! failed)
		{
			for(int i = 0; i < nRow; i ++)
				for(int j = 0; j < nCol; j ++)
				{
					int u = i, v = j + nRow;
					setEdge(u, v, downlim[i][j], uplim[i][j]);
				}
		}
		addEdge(tVtx_old, sVtx_old, 0, INF_F);
		adjust();
#ifdef DEBUG
		debug();
#endif
		dinic(sVtx_new, tVtx_new);
		for(Edge *e = begin[sVtx_new]; e; e = e->next)
			if(e->cap != 0)
			{
				failed = true;	
				break;
			}
		if(! failed)
		{
			for(int u = 0; u < nRow; u ++)
				for(Edge *e = begin[u]; e; e = e->next)
				{
					int v = e->t;
					ans[u][v - nRow] = e->downlim + e->cap_cp - e->cap;
				}
			for(int i = 0; i < nRow; i ++)
			{
				for(int j = 0; j < nCol - 1; j ++)
					fprintf(fout, VAL_F_FMT " ", ans[i][j]);
				fprintf(fout, VAL_F_FMT "\n", ans[i][nCol - 1]);
			}
		}
		else
			fprintf(fout, "IMPOSSIBLE\n");
		fprintf(fout, "\n");
	}
}

inline void Solve::setRes(int i, int j, char ctrl, int val)
{
	if(ctrl == '>')
		downlim[i][j] = MAX(downlim[i][j], val + 1);
	else if(ctrl == '<')
		uplim[i][j] = MIN(uplim[i][j], val - 1);
	else
		uplim[i][j] = downlim[i][j] = val;
	if(uplim[i][j] < downlim[i][j])
		failed = true;
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
