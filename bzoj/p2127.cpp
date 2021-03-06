#include <cstdio>
#include <cstring>
#include <algorithm>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
const int MAXN = 101;
const int VTX_MAX = 10002;
const int EDGE_MAX = 10 * (3 * VTX_MAX);
const int INFINITY = 0x3f3f3f3f;
int n, m, w1[MAXN][MAXN], w2[MAXN][MAXN], w3[MAXN][MAXN], w4[MAXN][MAXN], w5[MAXN][MAXN], w6[MAXN][MAXN];
int res = 0;
struct edge_t
{
	int vtx, cap;
	edge_t *next, *inverse;
} edge[EDGE_MAX], *begin[VTX_MAX], *cur[VTX_MAX];
int nVtx, nEdge, level[VTX_MAX];
edge_t *makeEdge(int u, int v, int c)/*{{{*/
{
	edge_t *e = &edge[nEdge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e, e->cap = c;
	return e;
}

void addEdge(int u, int v, int c)
{
	edge_t *e1 = makeEdge(u, v, c), *e2 = makeEdge(v, u, 0);
	e1->inverse = e2, e2->inverse = e1;
}/*}}}*/

bool preLable(int sVtx, int tVtx)
{
	static int queue[VTX_MAX];
	int head = 0, tail = 1;
	memset(level, -1, sizeof(int) * nVtx);
	queue[0] = sVtx, level[sVtx] = 0;
	for(; head != tail; head ++)
	{
		int u = queue[head];
		for(edge_t *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(level[v] != -1)
					continue;
				level[v] = level[u] + 1;
				if(v == tVtx) return true;
				queue[tail ++] = v;
			}
	}
	return false;
}

int aug(int u, int tVtx, int flow)
{
	if(u == tVtx)
		return flow;
	int res = 0;
	edge_t *e;
	for(e = cur[u]; e; e = e->next)
		if(e->cap && level[u] + 1 == level[e->vtx])
			if(int tmp = aug(e->vtx, tVtx, MIN(flow, e->cap)))
			{
				e->cap -= tmp, e->inverse->cap += tmp;
				cur[u] = e;
				flow -= tmp;
				res += tmp;
				if(flow == 0)
					break;
			}
	if(! e)
		level[u] = INFINITY;
	return res;
}

int dinic(int sVtx, int tVtx)
{
	int maxflow = 0;
	while(preLable(sVtx, tVtx))
	{
		memcpy(cur, begin, sizeof(edge_t *) * nVtx);
		while(int tmp = aug(sVtx, tVtx, INFINITY))
			maxflow += tmp;
	}
	return maxflow;
}
inline int point2Idx(int i, int j)
{
	return (i - 1) * m + j - 1;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	nVtx = n * m + 2;
	int sVtx = nVtx - 2, tVtx = nVtx - 1;
	int t;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &t);
			res += t * 2;
			w1[i][j] += t * 2;
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &t);
			res += t * 2;
			w2[i][j] += t * 2;
		}
	for(int i = 1; i < n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &t);
			res += t * 2;
			w3[i][j] = t;
			w1[i][j] += t, w1[i + 1][j] += t;
		}
	for(int i = 1; i < n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &t);
			res += t * 2;
			w4[i][j] = t;
			w2[i][j] += t, w2[i + 1][j] += t;
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < m; j ++)
		{
			scanf("%d", &t);
			res += t * 2;
			w5[i][j] = t;
			w1[i][j] += t, w1[i][j + 1] += t;
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < m; j ++)
		{
			scanf("%d", &t);
			res += t * 2;
			w6[i][j] = t;
			w2[i][j] += t, w2[i][j + 1] += t;
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			int u = point2Idx(i,j);
			addEdge(sVtx, u, w1[i][j]);
			addEdge(u, tVtx, w2[i][j]);
		}
	for(int i = 1; i < n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			int u = point2Idx(i, j), v = point2Idx(i + 1, j);
			addEdge(u, v, w3[i][j] + w4[i][j]), addEdge(v, u, w3[i][j] + w4[i][j]);
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < m; j ++)
		{
			int u = point2Idx(i, j), v = point2Idx(i, j + 1);
			addEdge(u, v, w5[i][j] + w6[i][j]), addEdge(v, u, w5[i][j] + w6[i][j]);
		}
	printf("%d\n", (res - dinic(sVtx, tVtx)) / 2);
}
