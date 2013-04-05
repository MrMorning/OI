#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int V_MAX = 100;
const int E_MAX = 10000;
const int K_MAX = 500;

typedef long long ll;
typedef pair<int, vector<int> > path_t;

struct Edge
{
	int to, dist;
	Edge *next;
} edge[E_MAX * 2], *begin[V_MAX];

path_t path[K_MAX];
int g[V_MAX];

int nv, ne, kth;
int sv, tv;
bool vis[V_MAX];
int pre[V_MAX];

void addEdge(int u, int v, int w)
{
	static int edgeCnt = 0;
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], e->dist = w;
	begin[u] = e;
}

void spfa(int sv)
{
	static int queue[V_MAX];
	static bool inQ[V_MAX];
	memset(g, 0x3f, sizeof(g));
	memset(inQ, 0, sizeof(inQ));
	int qh = 0, qt = 0;
	queue[qt ++] = sv;
	inQ[sv] = true;
	g[sv] = 0;
	while(qh != qt)
	{
		int u = queue[qh];
		inQ[u] = false;
		qh = (qh + 1) % nv;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			int tmp = g[u] + e->dist;
			if(tmp < g[v])
			{
				g[v] = tmp;
				if(!inQ[v])
				{
					inQ[v] = true;
					queue[qt] = v;
					qt = (qt + 1) % nv;
				}
			}
		}
	}
}

int belowCnt, kthLen;

path_t createPath(int dist)
{
	static path_t p;
	p.first = dist;
	p.second.clear();
	int i = tv;
	while(i != -1)
		p.second.push_back(i), i = pre[i];
	return p;
}

void dfs(int u, int dist)
{
	if(belowCnt >= kth)
		return;
	if(u == tv)
	{
		path[belowCnt ++] = createPath(dist);
		return;
	}

	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(!vis[v] && dist + e->dist + g[v] <= kthLen)
		{
			vis[v] = true;
			pre[v] = u;
			dfs(v, dist + e->dist);
			pre[v] = -1;
			vis[v] = false;
		}
	}
}

int main()
{

	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &nv, &ne, &kth);
	for(int i = 0, u, v, w; i < ne; i ++)
	{
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		addEdge(u, v, w); addEdge(v, u, w);
	}
	scanf("%d%d", &sv, &tv);
	sv --, tv --;
	spfa(tv);

	vis[sv] = true;
	memset(pre, -1, sizeof(pre));
	int lb = 0, rb = 1000000;
	//(lb, rb]
	for(int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
	{
		kthLen = mid;
		belowCnt = 0;
		dfs(sv, 0);
		if(belowCnt < kth)
			lb = mid;
		else
			rb = mid;	
	}

	printf("%d", rb);
	kthLen = rb, belowCnt = 0;
	dfs(sv, 0);
	sort(path, path + belowCnt);
	printf(" %d\n", path[kth - 1].second.size());
	for(int i = (int)path[kth - 1].second.size() - 1; i >= 0; i --)
		printf("%d ", path[kth - 1].second[i] + 1);
}
