#include <cstdio>
#include <cstring>
typedef long long bignum_t;
#define BIGNUM_T_FMT "%lld"
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_VTX_MAX = 5002;
const int N_EDGE_MAX = (60000 + 2 * N_VTX_MAX) * 2;
const bignum_t INFINITY = 10000000000000000LL;

struct Edge
{
	int vtx;
	bignum_t cap;
	Edge *next, *inverse;
};
Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX], *cur[N_VTX_MAX];
int n_edge, n_vtx;
int dist[N_VTX_MAX];

Edge *make_edge(int u, int v, bignum_t cap)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], e->cap = cap;
	return begin[u] = e;
}

void add_edge(int u, int v, bignum_t cap)
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
	while(head != tail)
	{
		int u = queue[head ++];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap)
			{
				int v = e->vtx;
				if(dist[v] != -1) continue;
				dist[v] = dist[u] + 1;
				if(v == t_vtx)
					return true;
				queue[tail ++] = v;
			}
	}
	return false;
}
bignum_t find_aug(int u, int t_vtx, bignum_t flow)
{
	if(u == t_vtx)
		return flow;
	Edge *e;
	bignum_t ret = 0;
	for(e = cur[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(dist[v] == dist[u] + 1)
			{
				if(bignum_t tmp = find_aug(v, t_vtx, MIN(flow, e->cap)))
				{
					e->cap -= tmp;
					e->inverse->cap += tmp;
					flow -= tmp;
					ret += tmp;
					cur[u] = e;
					if(! flow)
						break;
				}
			}
		}
	if(! e)
		dist[u] = -1;
	return ret;
}
bignum_t dinic(int s_vtx, int t_vtx)
{
	bignum_t ret = 0;
	while(pre_lable(s_vtx, t_vtx))
	{
		memcpy(cur, begin, sizeof(Edge *) * n_vtx);
		if(bignum_t tmp = find_aug(s_vtx, t_vtx, INFINITY))
			ret += tmp;
	}
	return ret;
}
void dfs(int u, int &cnt)
{
	static bool vis[N_VTX_MAX];
	cnt ++;
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->vtx;
			if(! vis[v])
				dfs(v, cnt);
		}
}
int main()
{
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	n_vtx = n + 2;
	int s_vtx = n_vtx - 2, t_vtx = n_vtx - 1;
	bignum_t acc = 0;
	for(int i = 0; i < n; i ++)
	{
		bignum_t t;
		scanf(BIGNUM_T_FMT , &t);
		t = t * 10000 - 1;
		if(t > 0)
		{
			add_edge(s_vtx, i, t);
			acc += t;
		}
		else if(t < 0)
			add_edge(i, t_vtx, -t);
	}
	for(int i = 0, u, v; i < m; i ++)
	{
		scanf("%d%d", &u, &v);
		u --, v --;
		add_edge(u, v, INFINITY);
	}
	bignum_t ans = acc - dinic(s_vtx, t_vtx);
	if(ans != 0)
		ans = (ans - 1) / 10000 + 1;
	int cnt = 0;
	dfs(s_vtx, cnt);
	printf("%d " BIGNUM_T_FMT "\n", cnt - 1, ans);
}
