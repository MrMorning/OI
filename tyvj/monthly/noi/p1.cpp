#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge
{
	int to, cap;
	Edge *next, *inv;
};

const int N_VTX_MAX = 5002;
const int N_EDGE_MAX = 4000000;
const int INFINITY = 0x3f3f3f3f;

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
int n_edge, n_vtx, s_vtx, t_vtx;
int dist[N_VTX_MAX];

Edge *make_edge(int u, int v, int w)
{
	Edge *e = &edge[n_edge ++];
	e->to = v, e->cap = w, e->next = begin[u];
	return begin[u] = e;
}

void add_edge(int u, int v, int w)
{
	Edge *e1 = make_edge(u, v, w),
		 *e2 = make_edge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

bool pre_lable()
{
	static int queue[N_VTX_MAX];
	int qh = 0, qt = 0;
	queue[qt ++] = s_vtx;
	memset(dist, -1, sizeof(int) * n_vtx);
	dist[s_vtx] = 0;
	while(qh < qt)
	{
		int u = queue[qh ++];
		for(Edge *e = begin[u]; e; e = e->next)
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
	return dist[t_vtx] != -1;
}

int aug(int u, int flow)
{
	if(u == t_vtx)
		return flow;
	Edge *e;
	int res = 0;
	for(e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->to;
			if(dist[v] != dist[u] + 1)
				continue;
			if(int tmp = aug(v, min(flow, e->cap)))
			{
				res += tmp;
				flow -= tmp;
				e->cap -= tmp;
				e->inv->cap += tmp;
				cur[u] = e;
				if(!flow)
					break;
			}
		}
	if(!e)
		dist[u] = -1;
	return res;
}

int dinic()
{
	int res = 0;
	while(pre_lable())
	{
		memcpy(cur, begin, sizeof(Edge*) * n_vtx);
		res += aug(s_vtx, INFINITY);
	}
	return res;
}
int main()
{
	freopen("t.in", "r", stdin);
	int n, m, sum = 0;
	scanf("%d%d", &n, &m);
	n_vtx = n + m + 2;
	s_vtx = n_vtx - 2, t_vtx = n_vtx - 1;
	for(int i = 0, a, b, c, d; i < n; i ++)
	{
		scanf("%d%d", &a, &b);
		sum += a;
		add_edge(i, t_vtx, a);
		while(b --)
		{
			scanf("%d%d", &c, &d);
			c --;
			add_edge(c + n, i, d);
		}
	}
	for(int i = 0, t; i < m; i ++)
	{
		scanf("%d", &t);
		add_edge(s_vtx, i + n, t);
	}
	printf("%d\n", sum - dinic());
}
