/*
 * $Date: Sat Feb 26 18:16:34 CST 2011
 * $Author: csimstu
 * $Prob: poj1988
 * $Sol: dinic
 */
#define INPUT 	"t.in"
#define OUTPUT 	"t.out"
//#define STDIO
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#include <cstdio>
#include <cstring>

namespace Solve
{
	typedef int Val_t;
#define VAL_T_FMT "%d"

	const Val_t INFINITY = 1 << 29;

	const int N_VTX_MAX = 51 * 2,
#define SQR(x) ((x) * (x))
		  	 N_EDGE_MAX = SQR(N_VTX_MAX);
#undef SQR
	class Edge
	{
		public:
			int vtx;
			Edge *next, *inverse;
			Val_t cap;
	};
	Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
	Val_t cap_t[N_EDGE_MAX];
	int nVtx, nEdge, dist[N_VTX_MAX];

	Edge *addEdge(int a, int b, Val_t c);
	void makeEdge(int a, int b, Val_t c);

	bool preLabel(int sVtx, int tVtx);
	Val_t findAug(int u, int tVtx, Val_t flow);
	Val_t dinic(int sVtx, int tVtx);

	void solve(FILE *fin, FILE *fout);
}

Solve::Edge *Solve::addEdge(int a, int b, Solve::Val_t c)
{
	nEdge ++;
	edge[nEdge].next = begin[a];
	begin[a] = &edge[nEdge];
	edge[nEdge].vtx = b;
	edge[nEdge].cap = c;
	return &edge[nEdge];
}

void Solve::makeEdge(int a, int b, Solve::Val_t c)
{
	Edge *e0 = addEdge(a, b, c);
	Edge *e1 = addEdge(b, a, 0);
	e0->inverse = e1, e1->inverse = e0;
}

Solve::Val_t Solve::dinic(int sVtx, int tVtx)
{
	for(int i = 0; i <= nEdge; i ++)

		cap_t[i] = edge[i].cap;
	Val_t maxFlow = 0;
	while(preLabel(sVtx, tVtx))
	{
		memcpy(cur, begin, sizeof(Edge *) * nVtx);
		while(Val_t tmp = findAug(sVtx, tVtx, INFINITY))
			maxFlow = MIN(INFINITY, tmp + maxFlow);
	}
	for(int i = 0; i <= nEdge; i ++)
		edge[i].cap = cap_t[i];
	return maxFlow;
}

bool Solve::preLabel(int sVtx, int tVtx)
{
	static int queue[N_VTX_MAX];
	memset(dist, -1, sizeof(int) * nVtx);
	queue[0] = sVtx, dist[sVtx] = 0;
	for(int head = 0, tail = 1; head != tail; head ++)
	{
		int u = queue[head];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(dist[v] == -1)
				{
					dist[v] = dist[u] + 1;
					queue[tail ++] = v;
					if(v == tVtx)
						return true;
				}
			}
	}
	return false;
}

Solve::Val_t Solve::findAug(int u, int tVtx, Val_t flow)
{
	if(u == tVtx)
		return flow;
	for(Edge *e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(dist[v] == dist[u] + 1)
				if(Val_t tmp = findAug(v, tVtx, MIN(flow, e->cap)))
				{
					e->cap -= tmp, e->inverse->cap += tmp;
					cur[u] = e;
					return tmp;
				}
		}
	return (Val_t) 0;
}

#define ST(x) ((x)*2)
#define EN(x) ((x)*2+1)
const int N_BUFFER_MAX = 1024 * 1024;
char buffer[N_BUFFER_MAX * sizeof(char)];
int bufferLen;
bool readInt(int &x)
{
	static int i = 0;
	while(i < bufferLen && ! (buffer[i] <= '9' && buffer[i] >= '0'))
		i ++;
	if(i == bufferLen)
		return false;
	int cnt = 0;
	while(buffer[i] <= '9' && buffer[i] >= '0')
		cnt = cnt * 10 + buffer[i] - '0', i ++;
	x = cnt;
	return true;
}
int n, m;
void Solve::solve(FILE *fin, FILE *fout)
{
	fread(buffer, sizeof(char), N_BUFFER_MAX, fin);
	bufferLen = strlen(buffer);
	while(readInt(n) && readInt(m))
	{
		if(n == 0 || m == 0)
		{
			if(n != 1 && m == 0)
				fprintf(fout, "0\n");
			else
				fprintf(fout, "1\n");
			continue;
		}
		nVtx = n * 2;
		nEdge = -1;
		memset(begin, 0, sizeof(Edge *) * nVtx);
		for(int i = 1, a, b; i <= m; i ++)
		{
			readInt(a), readInt(b);
			makeEdge(EN(a), ST(b), INFINITY);
			makeEdge(EN(b), ST(a), INFINITY);
		}
		for(int u = 0; u < n; u ++)
			makeEdge(ST(u), EN(u), 1);
		Val_t ans = INFINITY;
		for(int des = 0; des < n; des ++)
			for(int u = 0; u < n; u ++)
				if(u != des)
					ans = MIN(ans, dinic(EN(des), ST(u)));
		if(ans == INFINITY)
			ans = n;
		fprintf(fout, VAL_T_FMT "\n", ans);
	}
}
#undef ST
#undef EN

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin 	= fopen(INPUT, "r"),
		 *fout	= fopen(OUTPUT, "w");
	Solve::solve(fin, stdout);
	fclose(fin), fclose(fout);
#endif
	return 0;
}
