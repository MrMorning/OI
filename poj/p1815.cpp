#include <cstdio>
#include <cstring>
#include <queue>
#define ST(x) ((x)*2)
#define EN(x) ((x)*2+1)
#define VTX_MAXN 410
#define EDGE_MAXN 5010 * 2
#define INFINITY 0x3f3f3f3f
inline int min(int a, int b)
{
	return a < b ? a : b;
}
struct Edge
{
	int s, t, cap;
	Edge *next, *inverse;
	Edge(){};
	Edge(int _s, int _t, int _cap, Edge *_next): s(_s), t(_t), cap(_cap), next(_next){};
} edge[EDGE_MAXN];
Edge *begin[VTX_MAXN], *cur[VTX_MAXN];
int edgeCnt = -1, dist[VTX_MAXN];
int cap_t[EDGE_MAXN];
int nVtx, ans[VTX_MAXN], ansNum;

Edge *addEdge(int s, int t, int cap)
{
	edgeCnt ++;
	edge[edgeCnt] = Edge(s, t, cap, begin[s]);
	begin[s] = &edge[edgeCnt];
	return &edge[edgeCnt];
}

void makeEdge(int s, int t, int cap)
{
	Edge *e1 = addEdge(s, t, cap), *e2 = addEdge(t, s, 0);
	e1->inverse = e2;
	e2->inverse = e1;
}

bool label(int sVtx, int tVtx)
{
	static int queue[VTX_MAXN];
	queue[0] = sVtx;
	memset(dist, -1, sizeof(int) * nVtx);
	dist[sVtx] = 0;
	for(int head = 0, tail = 1; head != tail; head ++)
	{
		int u = queue[head];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->t;
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

int findArg(int u, int tVtx, int flow)
{
	if(u == tVtx)
		return flow;
	for(Edge *e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->t;
			if(dist[v] == dist[u] + 1)
				if(int tmp = findArg(v, tVtx, min(flow, e->cap)))
				{
					e->cap -= tmp;
					e->inverse->cap += tmp;
					cur[u] = e;
					return tmp;
				}
		}
	return 0;
}

int dinic(int sVtx, int tVtx)
{
	for(int i = 0; i <= edgeCnt; i ++)
		cap_t[i] = edge[i].cap;
	int flow = 0;
	while(label(sVtx, tVtx))
	{
		memcpy(cur, begin, sizeof(Edge*) * nVtx);
		while(int tmp = findArg(sVtx, tVtx, INFINITY))
			flow += tmp;
	}
	for(int i = 0; i <= edgeCnt; i ++)
		edge[i].cap = cap_t[i];
	return flow;
}

void solve()
{
	freopen("t.in", "r", stdin);
	int n, st, en;
	scanf("%d%d%d", &n, &st, &en);
	st --, en --;
	nVtx = n * 2;
	for(int i = 0; i < n; i ++)
		for(int j = 0, t; j < n; j ++)
		{
			scanf("%d", &t);
			if(t == 0)
				continue;
			makeEdge(EN(i), ST(j), INFINITY);
		}
	for(int i = 0; i < n; i ++)
		if(i != st && i != en)
			makeEdge(ST(i), EN(i), 1);
		else
			makeEdge(ST(i), EN(i), INFINITY);
	int cnt = dinic(ST(st), EN(en));
	for(int u = 0; u < n; u ++)
	{
		if(u == st || u == en)
			continue;
		Edge *curE = begin[ST(u)];
		while(curE && (curE->t != EN(u) || curE->cap == 0))
			curE = curE->next;
		if(! curE)
			continue;
		curE->cap = curE->inverse->cap = 0;
		if(dinic(ST(st), EN(en)) == cnt - 1)
		{
			cnt --;
			ans[++ ansNum] = u + 1;
			if(cnt == 0)
				break;
		}
		else
			curE->cap = curE->inverse->cap = 1;
	}
	if(cnt > 0)
		printf("NO ANSWER!\n");
	else
	{
		printf("%d\n", ansNum);
		for(int i = 1; i < ansNum; i ++)
			printf("%d ", ans[i]);
		if(ansNum > 0)
			printf("%d\n", ans[ansNum]);
	}
}

int main()
{
	solve();
}
