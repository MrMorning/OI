#include <cstdio>
#include <algorithm>

using namespace std;

const int N_VTX_MAX = 100000;
const int N_EDGE_MAX = 100000 * 2 - 1;
const int INFINITY = 0x3f3f3f3f;

struct Edge
{
	int vtx;
	Edge *next;
};

Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
int n_edge;
int f[N_VTX_MAX][3][2];

void add_edge(int u, int v)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}

void dp(int u, int p)
#define UPD(x, y) x = std::max(x, y);
{
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(v != p)
			dp(v, u);
	}
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(v == p) continue;
		for(int j = 2; j >= 0; j --)
		{
			for(int t = j; t >= 0; t --)
			{
				UPD(f[u][j][0], f[v][t][0] + f[u][j - t][0]);
				UPD(f[u][j][1], f[v][t][0] + f[u][j - t][1]);
				UPD(f[u][j][1], f[v][t][1] + f[u][j - t][0] + 1);
			}
			for(int t = 0; t < j; t ++)
				UPD(f[u][j][0], f[v][t][1] + f[u][j - t - 1][1] + 1);
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 0, u, v; i < n - 1; i ++)
	{
		scanf("%d%d", &u, &v);
		u --, v --;
		add_edge(u, v);
		add_edge(v, u);
	}
	dp(0, -1);
	int ans = std::max(f[0][k][0], f[0][k - 1][1]);
	ans = std::max(ans, f[0][1][0]);
	printf("%d\n", 2 * n - 2 - ans + k);
}
