#include <cstdio>
#include <cassert>
#include <cstring>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? - (x) : (x))

const int INFINITY = 0x3f3f3f3f;
const int N_VTX_MAX = 20 * 20 * 2 + 2;
const int N_EDGE_MAX = N_VTX_MAX * N_VTX_MAX;

struct Edge
{
	int vtx, cap;
	Edge *next, *inverse;
};

int edge_idx = 0, n_vtx;
Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
int dist[N_VTX_MAX];

Edge *make_edge(int, int, int);
void add_edge(int, int, int);

bool pre_lable(int, int);
int find_aug(int, int, int);
int dinic(int, int);

inline int point_to_idx(int, int);

Edge *make_edge(int u, int v, int cap)
{
	Edge *e = &edge[edge_idx ++];
	e->vtx = v, e->cap = cap, e->next = begin[u], begin[u] = e;
	return e;
}
void add_edge(int u, int v, int cap)
{
	Edge *e1 = make_edge(u, v, cap),
		 *e2 = make_edge(v, u, 0);
	e1->inverse = e2, e2->inverse = e1;
}
bool pre_lable(int s_vtx, int t_vtx)
{
	static int queue[N_VTX_MAX];
	memset(dist, -1, sizeof(int) * n_vtx);
	int head = 0, tail = 0;

	queue[tail ++] = s_vtx, dist[s_vtx] = 0;
	while(head < tail)
	{
		int u = queue[head ++];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(dist[v] == -1)
				{
					dist[v] = dist[u] + 1;
					queue[tail ++] = v;
				}
			}
	}
	return dist[t_vtx] != -1;
}
int find_aug(int u, int t_vtx, int flow)
{
	if(u == t_vtx)
		return flow;
	Edge *e;
	int ret = 0;
	for(e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(dist[v] == dist[u] + 1)
				if(int tmp = find_aug(v, t_vtx, MIN(flow, e->cap)))
				{
					ret += tmp;
					e->cap -= tmp, e->inverse->cap += tmp;
					cur[u] = e;
					flow -= tmp;
					if(flow == 0)
						break;
				}
		}
	if(! e)
		dist[u] = -1;
	return ret;
}
int dinic(int s_vtx, int t_vtx)
{
	int maxflow = 0;
	while(pre_lable(s_vtx, t_vtx))
	{
		memcpy(cur, begin, sizeof(Edge *) * n_vtx);
		while(int tmp = find_aug(s_vtx, t_vtx, INFINITY))
			maxflow += tmp;
	}
	return maxflow;
}
int r, c, d;
#define IN_VTX(x) (x)
#define OUT_VTX(x) ((x) + r * c)
inline int point_to_idx(int i, int j)
{
	return i * c + j;
}
int main()
{
	freopen("t.in", "r", stdin);
	
	scanf("%d%d%d\n", &r, &c, &d);

	n_vtx = r * c * 2 + 2;
	int s_vtx = n_vtx - 2, t_vtx = n_vtx - 1;

	for(int i = 0; i < r; i ++)
	{
		char ch;
		for(int j = 0; j < c; j ++)
		{
			int u = point_to_idx(i, j);

			if(MIN(i + 1, j + 1) <= d || MIN(r - i, c - j) <= d)
				add_edge(OUT_VTX(u), t_vtx, INFINITY);

			scanf("%c", &ch);
			if(ch - '0' > 0)
				add_edge(IN_VTX(u), OUT_VTX(u), ch - '0');

			for(int k = - d; k <= d; k ++)
				for(int s = - d; s <= d; s ++)
					if(i + k >= 0 && i + k < r)
						if(j + s >= 0 && j + s < c)
							if(ABS(k) + ABS(s) <= d)
							{
								int v = point_to_idx(i + k, j + s);
								add_edge(OUT_VTX(u), IN_VTX(v), INFINITY);
							}

			scanf("\n");
		}
	}
	int lizard_cnt = 0;

	for(int i = 0; i < r; i ++)
	{
		char ch;
		for(int j = 0; j < c; j ++)
		{
			int u = point_to_idx(i, j);

			scanf("%c", &ch);
			if(ch == 'L')
			{
				lizard_cnt ++;
				add_edge(s_vtx, IN_VTX(u), 1);
			}
		}

		scanf("\n");
	}
	printf("%d\n", lizard_cnt - dinic(s_vtx, t_vtx));
}
