#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

typedef pair<int, int> state_t;

const int N_VTX_MAX = 501;
const int N_EDGE_MAX = 10000;
const int VAL_MAX = 30000;
const int N_QUEUE_MAX = 1000000;

int gcd(int a, int b)
{return b ? gcd(b, a % b) : a;}

struct Edge
{
	int vtx, dist;
	Edge *next;
};

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
int n_edge, n_vtx;
int dist[N_VTX_MAX][VAL_MAX];

void add_edge(int u, int v, int w)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], e->dist = w;
	begin[u] = e;
}

void spfa(int s_vtx)
{
	static state_t queue[N_QUEUE_MAX];
	static bool in_q[N_VTX_MAX][VAL_MAX];

	memset(in_q, 0, sizeof(bool) * n_vtx);
	memset(dist, 0, sizeof(dist));
	dist[s_vtx][0] = VAL_MAX - 1;
	queue[0] = make_pair(s_vtx, 0);
	for(int qh = 0, qt = 1; qh != qt; qh = (qh + 1) % N_QUEUE_MAX)
	{
		state_t u = queue[qh];
		in_q[u.first][u.second] = false;
		for(Edge *e = begin[u.first]; e; e = e->next)
		{
			int v = e->vtx;
			int w = max(u.second, e->dist);
			if(w >= VAL_MAX) continue;
			int tmp = min(dist[u.first][u.second], e->dist);
			if(dist[v][w] < tmp)
			{
				dist[v][w] = tmp;
				if(! in_q[v][w])
				{
					in_q[v][w] = true;
					queue[qt] = make_pair(v, w);
					qt = (qt + 1) % N_QUEUE_MAX;
				}
			}
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int m;
	scanf("%d%d", &n_vtx, &m);
	while(m --)
	{
		int x, y, v;
		scanf("%d%d%d", &x, &y, &v);
		x --, y --;
		add_edge(x, y, v);
		add_edge(y, x, v);
	}
	int s_vtx, t_vtx;
	scanf("%d%d", &s_vtx, &t_vtx);
	s_vtx --, t_vtx --;
	spfa(s_vtx);
	bool deepin = false;
	int ans_a = VAL_MAX, ans_b = 1;
	for(int i = 0; i < VAL_MAX; i ++)
		if(dist[t_vtx][i] != 0)
		{
			deepin = true;
			int a = i, b = dist[t_vtx][i];
			int tmp = gcd(a, b);
			a /= tmp, b /= tmp;
			if(a * ans_b < b * ans_a)
				ans_a = a, ans_b = b;
		}
	if(! deepin)
		printf("IMPOSSIBLE\n");
	else
		if(ans_b > 1)
			printf("%d/%d\n", ans_a, ans_b);
		else
			printf("%d\n", ans_a);
}
