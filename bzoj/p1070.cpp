#include <cstdio>
#include <cstring>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_VTX_MAX = 9 * 60 + 60 + 2;
const int N_EDGE_MAX = N_VTX_MAX * (N_VTX_MAX + 2);
const int INFINITY = 0x3f3f3f3f;

struct Edge
{
	int vtx, cap, dist;
	Edge *next, *inverse;
};

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
bool vis[N_VTX_MAX];
int dist[N_VTX_MAX];
int n_edge, n_vtx;
int fee[60][60];

Edge *make_edge(int u, int v, int cap, int dist)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], e->cap = cap, e->dist = dist;
	return begin[u] = e;
}

void add_edge(int u, int v, int cap, int dist)
{
	Edge *e1 = make_edge(u, v, cap, dist),
		 *e2 = make_edge(v, u, 0, - dist);
	e1->inverse = e2, e2->inverse = e1;
}

bool pre_lable(int s_vtx, int t_vtx)
{
	static int queue[N_VTX_MAX];
	static bool in_q[N_VTX_MAX];
	memset(in_q, 0, sizeof(bool) * n_vtx);
	memset(dist, 0x3f, sizeof(int) * n_vtx);
	int head = 0, tail = 0;
	queue[tail ++] = s_vtx, dist[s_vtx] = 0, in_q[s_vtx] = true;
	for(; head != tail; head = (head + 1) % n_vtx)
	{
		int u = queue[head]; in_q[u] = false;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(dist[v] > dist[u] + e->dist)
				{
					dist[v] = dist[u] + e->dist;
					if(! in_q[v])
					{
						in_q[v] = true;
						queue[tail] = v;
						tail = (tail + 1) % n_vtx;
					}
				}
			}
	}
	return dist[t_vtx] != INFINITY;
}
int find_aug(int u, int t_vtx, int flow)
{
	if(u == t_vtx)
		return flow;
	vis[u] = true;
	int ret = 0;
	Edge *e;
	for(e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(! vis[v] && dist[v] == dist[u] + e->dist)
				if(int tmp = find_aug(v, t_vtx, MIN(flow, e->cap)))
				{
					ret += tmp;
					e->cap -= tmp, e->inverse->cap += tmp;
					cur[u] = e;
					return tmp;
					flow -= tmp;
					if(! flow)
						break;
				}
		}
	if(! e)
		dist[u] = INFINITY;
	return 0;
}
int dinic(int s_vtx, int t_vtx)
{
	int min_cost = 0;
	while(pre_lable(s_vtx, t_vtx))
	{
		memcpy(cur, begin, sizeof(Edge *) * n_vtx);
		memset(vis, 0, sizeof(bool) * n_vtx);
		if(int tmp = find_aug(s_vtx, t_vtx, INFINITY))
			min_cost += tmp * dist[t_vtx];
	}
	return min_cost;
}

int main()
{
	freopen("t.in", "r", stdin);
	int m, n;
	scanf("%d%d", &m, &n);
	n_vtx = m * n + n + 2;
	int s_vtx = n_vtx - 2, t_vtx = n_vtx - 1;

	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			scanf("%d", &fee[i][j]);

	for(int i = 0; i < n; i ++)
		add_edge(s_vtx, i, 1, 0);

	for(int j = 0; j < m; j ++)
		for(int i = 0; i < n; i ++)
			for(int k = 0; k < n; k ++)
				add_edge(k, j * n + i + n, 1, fee[k][j] * (i + 1));

	for(int j = 0; j < m; j ++)
		for(int i = 0; i < n; i ++)
			add_edge(j * n + i + n, t_vtx, 1, 0);
	printf("%.2lf\n", (double)dinic(s_vtx, t_vtx) / n);
}
