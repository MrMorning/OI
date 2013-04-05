#include <cstdio>
#include <cstring>
#include <algorithm>
const int N_VTX_MAX = 100;
const int N_EDGE_MAX = N_VTX_MAX * N_VTX_MAX;
struct Edge
{
	int u, v, w;
	bool e;
	bool operator< (const Edge &t) const
	{
		return w < t.w;
	}
};

Edge edge[N_EDGE_MAX];

int parent[N_VTX_MAX];
bool used[N_EDGE_MAX];
int buf[N_EDGE_MAX], n_buf;
int n_vtx, n_edge;

int find(int x)
{
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}
void merge(int x, int y)
{
	parent[find(x)] = find(y);
}

int mst()
{
	memset(used, 0, sizeof(used));
	int ret = 0, cnt = 0;
	for(int i = 0; i < n_vtx; i ++)
		parent[i] = i;
	for(int i = 0; i < n_edge; i ++)
		if(edge[i].e)
		{
			int p = find(edge[i].u),
				q = find(edge[i].v);
			if(p != q)
			{
				used[i] = true;
				ret += edge[i].w;
				merge(p, q);
				cnt ++;
			}
		}
	return cnt == n_vtx - 1 ? ret : 0;
}

void solve()
{
	scanf("%d%d", &n_vtx, &n_edge);
	for(int i = 0; i < n_edge; i ++)
	{
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
		edge[i].u --, edge[i].v --;
		edge[i].e = true;
	}
	std::sort(edge, edge + n_edge);
	n_buf = 0;
	int ans = mst();
	if(ans == 0)
	{
		printf("0\n");
		return;
	}
	for(int i = 0; i < n_edge; i ++)
		if(used[i])
			buf[n_buf ++] = i;
	for(int i = 0; i < n_buf; i ++)
	{
		int j = buf[i];
		edge[j].e = false;
		if(mst() == ans)
		{
			printf("Not Unique!\n");
			return;
		}
		edge[j].e = true;
	}
	printf("%d\n", ans);
}

int main()
{
	freopen("t.in", "r", stdin);
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
		solve();
}
