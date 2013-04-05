#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int V_MAX = 410;
const int E_MAX = 81000;
const int oo = 0x3f3f3f3f;

struct Edge
{
	int to, cap;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX];

int nv, ne, sv, tv;
int nstu, nuni;
int dist[V_MAX];
int edgeCnt;
int cnt[V_MAX];
int ans[V_MAX][2];

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

int main()
{
	scanf("%d%d", &nstu, &nuni);
	nv = nstu + nuni + 2;
	sv = nv - 2, tv = nv - 1;
	for(int i = 0; i < nstu; i ++)
	{
		addEdge(sv, i, 1);
		int k;
		scanf("%d", &k);
		while(k --)
		{
			int t;
			scanf("%d", &t);
			addEdge(i, t - 1 + nstu, oo);
		}
	}
	for(int i = nstu; i < nstu + nuni; i ++)
		addEdge(i, tv, 2);
	int res = dinic();
	if(res == 2 * nuni)
	{
		printf("YES\n");
		for(int i = 0; i < nstu; i ++)
		{
			for(Edge *e = begin[i]; e; e = e->next)
				if(e->to != sv && e->inv->cap == 1)
					ans[e->to - nstu][cnt[e->to - nstu] ++] = i;
		}
		for(int i = 0; i < nuni; i ++)
		{
			printf("2");
			for(int j = 0; j < 2; j ++)
				printf(" %d", ans[i][j] + 1);
			printf("\n");
		}
	}
	else
		printf("NO\n");
}
