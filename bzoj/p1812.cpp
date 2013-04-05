#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N_MAX = 110;

struct Edge
{
	int vtx;
	Edge *next;
};

int n, m, edge_cnt;
Edge *begin[N_MAX], edge[N_MAX];
int f[N_MAX][N_MAX][N_MAX], pre_f[N_MAX][N_MAX][N_MAX];
int w[N_MAX], len[N_MAX], pre[N_MAX];
int anc[N_MAX][N_MAX], dist[N_MAX][N_MAX];

void add_edge(int u, int v)
{
	Edge *e = &edge[edge_cnt ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}

void dp(int u, int d)
{
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		dp(v, d + 1);
		for(int k = 0; k <= d; k ++)
			for(int j = m; j >= 0; j --)
			{
				f[u][j][k] = 0x3f3f3f3f;
				for(int l = 0; l <= j; l ++)
				{
					if(j - l - 1 >= 0)
						f[u][j][k] = min(f[u][j][k], pre_f[u][j - l - 1][k] + f[v][l][0]);
					f[u][j][k] = min(f[u][j][k], pre_f[u][j - l][k] + f[v][l][k + 1] + w[v] * dist[v][k + 1]);
				}
			}
		memcpy(pre_f[u], f[u], sizeof(f[u]));
	}
}

void pre_work()
{
	for(int i = 1; i <= n; i ++)
	{
		add_edge(pre[i], i);
		for(int u = i, j = 0; u != 0; u = pre[u], j ++)
			anc[i][j] = u, dist[i][j + 1] = dist[i][j] + len[u];
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d%d", &w[i], &pre[i], &len[i]);
	pre_work();
	//	memset(f, 0x3f, sizeof(f));
	dp(0, 0);
	printf("%d\n", f[0][m][0]);
}
