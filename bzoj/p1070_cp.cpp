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

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *pre_edge[N_VTX_MAX];
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

bool spfa(int s_vtx, int t_vtx)
{
	static int queue[N_VTX_MAX];
	static bool in_queue[N_VTX_MAX];
	memset(dist, 0x3f, sizeof(int) * n_vtx);
	memset(in_queue, 0, sizeof(bool) * n_vtx);
	memset(pre_edge, 0, sizeof(Edge *) * n_vtx);
	int head = 0, tail = 0;
	queue[tail ++] = s_vtx, dist[s_vtx] = 0, in_queue[s_vtx] = true;

	while(head != tail)
	{
		int u = queue[head];
		in_queue[u] = false;
		head = (head + 1) % n_vtx;
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(dist[v] > dist[u] + e->dist)
				{
					dist[v] = dist[u] + e->dist;
					pre_edge[v] = e;
					if(! in_queue[v])
					{
						in_queue[v] = true;
						queue[tail] = v;
						tail = (tail + 1) % n_vtx;
					}
				}
			}
	}

	return dist[t_vtx] != INFINITY;
}

int mincost(int s_vtx, int t_vtx)
{
	int ret = 0;
	while(spfa(s_vtx, t_vtx))
	{
		Edge *e = pre_edge[t_vtx];
		int tmp = INFINITY;
		while(e)
		{
			tmp = MIN(tmp, e->cap);
			e = pre_edge[e->inverse->vtx];
		}

		e = pre_edge[t_vtx];
		while(e)
		{
			e->cap -= tmp;
			e->inverse->cap += tmp;
			e = pre_edge[e->inverse->vtx];
		}

		ret += tmp * dist[t_vtx];
	}
	return ret;
}

void test()
{
	int m, s_vtx, t_vtx, a, b, c, d;
	scanf("%d%d", &n_vtx, &m);
	scanf("%d%d", &s_vtx, &t_vtx);
	s_vtx --, t_vtx --;
	while(m --)
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a --, b --;
		add_edge(a, b, c, d);
	}
	printf("%d\n", mincost(s_vtx, t_vtx));
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
	printf("%.2lf\n", (double)mincost(s_vtx, t_vtx) / n);
}
