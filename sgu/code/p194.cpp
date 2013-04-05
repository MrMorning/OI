#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

const int V_MAX = 210;
const int E_MAX = 41000;
const int oo = 0x3f3f3f3f;

struct Edge
{
	int to, cap;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX], *pe[E_MAX];

struct Data
{
	int u, v, c, b;
} data[E_MAX];

int nv, ne, sv, tv;
int dist[V_MAX];
int remain[V_MAX];
int edgeCnt;

Edge *makeEdge(int u, int v, int w)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
	e->cap = w;
	return e;
}

void addEdge(int u, int v, int w)
{
	Edge *e1 = makeEdge(u, v, w),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

bool preLable()
{
	static int queue[V_MAX];

	int qh = 0, qt = 0;
	queue[qt ++] = sv;
	memset(dist, -1, sizeof(dist));
	dist[sv] = 0;
	while(qh < qt)
	{
		int u = queue[qh ++];
		for(Edge *e = begin[u]; e; e =e->next)
			if(e->cap)
			{
				int v = e->to;
				if(dist[v] == -1)
				{
					dist[v] = dist[u] + 1;
					queue[qt ++] = v;
				}
			}
	}
	return dist[tv] != -1;
}

int findAug(int u, int flow)
{
	if(u == tv)
		return flow;
	int res = 0;
	Edge *e;
	for(e = begin[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->to;
			if(dist[v] != dist[u] + 1)
				continue;
			int tmp = findAug(v, min(flow, e->cap));
			if(tmp)
			{
				flow -= tmp;
				e->cap -= tmp, e->inv->cap += tmp;
				res += tmp;
			}
			if(!flow)
				break;
		}
	if(!e)
		dist[u] = -1;
	return res;
}

int dinic()
{
	int res = 0;
	while(preLable())
		res += findAug(sv, oo);
	return res;
}

void construct()
{
	edgeCnt = 0;
	memset(begin, 0, sizeof(begin));
	memset(pe, 0, sizeof(pe));
	memset(remain, 0, sizeof(remain));
	for(int i = 0; i < ne; i ++)
	{
		Data &t = data[i];
		remain[t.v] -= t.b;
		remain[t.u] += t.b;
		addEdge(t.u, t.v, t.c - t.b);
		pe[i] = &edge[edgeCnt - 2];
	}
	sv = nv, tv = nv + 1;
	for(int i = 0; i < nv; i ++)
		if(remain[i] > 0)
			addEdge(i, tv, remain[i]);
		else if(remain[i] < 0)
			addEdge(sv, i, -remain[i]);
}

bool check()
{
	construct();
	dinic();
	for(Edge *e = begin[sv]; e; e = e->next)
		if(e->cap)
			return false;
	return true;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &ne);
	for(int i = 0; i < ne; i ++)
	{
		scanf("%d%d%d%d", &data[i].u, &data[i].v, &data[i].b, &data[i].c);
		data[i].u --, data[i].v --;
	}

	if(!check())
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for(int i = 0; i < ne; i ++)
		printf("%d\n", data[i].b + pe[i]->inv->cap);
}
