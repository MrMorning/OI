#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
const int VTX_MAX = 302;
const int EDGE_MAX = 2 * 300 * 300;
const int INFINITY = 0x3f3f3f3f;
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

int main()
{
	freopen("t.in", "r", stdin);
	int m, t, u, v;
	scanf("%d%d", &nVtx, &m);
	int sVtx = nVtx, tVtx = nVtx + 1;
	for(int i = 0; i < nVtx; i ++)
	{
		scanf("%d", &t);
		if(t) addEdge(sVtx, i, 1);
		else addEdge(i, tVtx, 1);
	}
	nVtx += 2;
	while(m --)
	{
		scanf("%d%d", &u, &v);
		u --, v --;
		addEdge(u, v, 1), addEdge(v, u, 1);
	}
	printf("%d\n", dinic(sVtx, tVtx));
}
