#include <cstdio>
#include <cassert>
#include <cstring>
#include <map>
using namespace std;

const int V_MAX = 11000;
const int E_MAX = 210000;

struct RealEdge
{
	int to;
	RealEdge *next;
} *realBegin[V_MAX];

struct FakeEdge
{
	int to;
	FakeEdge *next;
} *fakeBegin[V_MAX];

int realDgr[V_MAX], fakeDgr[V_MAX], belong[V_MAX];
bool used[V_MAX], vis[V_MAX];
map<int, int> marked[V_MAX];
int nv, ne, nfv, top;
int bal[V_MAX], path[E_MAX];

void addRealEdge(int u, int v)
{
	static RealEdge edge[E_MAX];
	static int edgeCnt = 0;
	RealEdge *e = &edge[edgeCnt ++];
	e->to = v, e->next = realBegin[u];
	realBegin[u] = e;
}

void makeFakeEdge(int u, int v)
{
	static FakeEdge edge[E_MAX];
	static int edgeCnt = 0;
	FakeEdge *e = &edge[edgeCnt ++];
	e->to = v, e->next = fakeBegin[u];
	fakeBegin[u] = e;
}

void addFakeEdge(int u, int v)
{
	makeFakeEdge(u, v);
	makeFakeEdge(v, u);
	fakeDgr[u] ++, fakeDgr[v] ++;
}

void dfs(int u)
{
	for(FakeEdge *e = fakeBegin[u]; e; e = e->next)
	{
		int v = e->to;
		if(!marked[u][v])
		{
			marked[u][v] = marked[v][u] = true;
			dfs(v);
		}
	}
	path[top ++] = u;
}

void dfs2(int u)
{
	vis[u] = true;
	for(RealEdge *e = realBegin[u]; e; e = e->next)
	{
		int v = e->to;
		if(!vis[v])
			dfs2(v);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &ne);
	for(int i = 0, u, v; i < ne; i ++)
	{
		scanf("%d%d", &u, &v);
		u --, v --;
		addRealEdge(u, v);
		addRealEdge(v, u);
		realDgr[u] ++, realDgr[v] ++;
	}
	dfs2(0);
	for(int i = 0; i < nv; i ++)
		if(!vis[i])
		{
			printf("-1\n");
			return 0;
		}
	memset(belong, -1, sizeof(belong));
	for(int i = 0; i < nv; i ++)
		if(belong[i] == -1)
		{
			belong[i] = nfv ++;
			if(realDgr[i] > 2)
				for(RealEdge *e = realBegin[i]; e; e = e->next)
					if(realDgr[e->to] > 2)
						belong[e->to] = belong[i];
		}
	int edgeNum = 0;
	memset(bal, -1, sizeof(bal));
	for(int i = 0; i < nv; i ++)
		if(realDgr[i] == 2)
		{
			bal[belong[i]] = i;
			int v1 = belong[realBegin[i]->to],
				v2 = belong[realBegin[i]->next->to],
				u = belong[i];
			addFakeEdge(u, v1);
			addFakeEdge(u, v2);
			edgeNum ++;
		}

	for(int i = 0; i < nfv; i ++)
		if(fakeDgr[i] % 2 == 1)
		{
			printf("-1\n");
			return 0;
		}

	dfs(belong[0]);
//	assert(top == edgeNum + 1);
	for(int i = 0; i < edgeNum; i ++)
	{
		int u = path[i];
		if(bal[u] < 0)
		{
			int ul = bal[path[(i - 1 + edgeNum) % edgeNum]],
				ur = bal[path[(i + 1 + edgeNum) % edgeNum]];
			for(RealEdge *e1 = realBegin[ul]; e1; e1 = e1->next)
				for(RealEdge *e2 = realBegin[ur]; e2; e2 = e2->next)
					if(belong[e1->to] == u && belong[e2->to] == u)
						printf("%d %d ", e1->to + 1, e2->to + 1);
		}
		else
			printf("%d ", bal[u] + 1);
	}

	//	for(int i = 0; i < nv; i ++)
	//		assert(used[i]);
}
