#include <cstdio>
#include <cstring>
const int N_EDGE_MAX = 2 * 1000000;
const int N_VTX_MAX = 1100000;
struct Edge
{
	int vtx;
	Edge *next;
} edge[N_EDGE_MAX], *begin[N_VTX_MAX];
int dist[N_VTX_MAX], n_edge, n_vtx;
inline void add_edge(int u, int v)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}
void bfs(int s_vtx, int t_vtx)
{
	static int queue[N_VTX_MAX];
	memset(dist, -1, sizeof(int) * n_vtx);
	int head = 0, tail = 0;
	queue[tail ++] = s_vtx, dist[s_vtx] = 0;
	while(head < tail)
	{
		int u = queue[head ++];
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			if(dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				if(v == t_vtx)
					return;
				queue[tail ++] = v;
			}
		}
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	int m;
	scanf("%d%d", &n_vtx, &m);
	int t_vtx = n_vtx - 1;
	for(int i = 0; i < m; i ++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		if(w == 2)
		{
			add_edge(u, n_vtx);
			add_edge(n_vtx, v);
			n_vtx ++;
		}
		else
			add_edge(u, v);
	}
	bfs(0, t_vtx);
	printf("%d\n", dist[t_vtx]);
}
