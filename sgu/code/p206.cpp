#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int V_MAX = 500;
const int E_MAX = 100000;
const int oo = 0x3f3f3f3f;

struct Edge
{
	int to, w;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];

struct Data
{
	int u, v, w;
} data[E_MAX];

int edgeCnt;
int slack, nv, ne;
int lx[V_MAX], ly[V_MAX];
int depth[V_MAX], father[V_MAX], preEdge[V_MAX];
bool visX[V_MAX], visY[V_MAX];
int match[V_MAX];
int weight[V_MAX][V_MAX];
int np;

void addEdge(int u, int v, int w)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], e->w = w;
	begin[u] = e;
}

void readData()
{
	scanf("%d%d", &nv, &ne);
	for(int i = 0, u, v, w; i < nv - 1; i ++)
	{
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		data[i].u = u, data[i].v = v, data[i].w = w;
		addEdge(u, v, i);
		addEdge(v, u, i);
	}
}

void dfs(int u, int p)
{
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(v == p)
			continue;
		father[v] = u;
		preEdge[v] = e->w;
		depth[v] = depth[u] + 1;
		dfs(v, u);
	}
}

void buildTree()
{
	dfs(0, -1);
}

int lca(int u, int v)
{
	while(u != v)
	{
		if(depth[u] > depth[v])
			u = father[u];
		else
			v = father[v];
	}
	return u;
}

void buildGraph()
{
	edgeCnt = 0;
	memset(begin, 0, sizeof(begin));
	for(int i = nv - 1; i < ne; i ++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		data[i].u = u, data[i].v = v, data[i].w = w;
		int p = lca(u, v);
		while(u != p)
		{
			int t = preEdge[u];
			if(data[t].w - w >= 0)
				weight[t][i - (nv - 1)] = data[t].w - w;
			u = father[u];
		}
		while(v != p)
		{
			int t = preEdge[v];
			if(data[t].w - w >= 0)
				weight[t][i - (nv - 1)] = data[t].w - w;
			v = father[v];
		}
	}
	np = max(nv - 1, ne - nv + 1);
}

bool aug(int u)
{
	visX[u] = true;
	for(int v = 0; v < np; v ++)
	{
		if(visY[v])
			continue;
		int t = lx[u] + ly[v] - weight[u][v];
		if(t == 0)
		{
			visY[v] = true;
			if(match[v] == -1 || aug(match[v]))
			{
				match[v] = u;
				return true;
			}
		}
		else
			slack = min(slack, t);
	}
	return false;
}

void KM()
{
	memset(match, -1, sizeof(match));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));

	for(int i = 0; i < np; i ++)
		for(int j = 0; j < np; j ++)
			if(weight[i][j] > lx[i])
				lx[i] = weight[i][j];
	for(int x = 0; x < np; x ++)
	{
		while(1)
		{
			memset(visX, 0, sizeof(visX));
			memset(visY, 0, sizeof(visY));
			slack = oo;
			if(aug(x))
				break;
			for(int i = 0; i < np; i ++)
			{
				if(visX[i])
					lx[i] -= slack;
				if(visY[i])
					ly[i] += slack;
			}
		}
	}
	for(int i = 0; i < nv - 1; i ++)
		printf("%d\n", data[i].w - lx[i]);
	for(int i = nv - 1; i < ne; i ++)
		printf("%d\n", data[i].w + ly[i - (nv - 1)]);
}

int main()
{
	freopen("t.in", "r", stdin);
	readData();
	buildTree();
	buildGraph();
	KM();
}
