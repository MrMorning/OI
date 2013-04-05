#include <cstdio>
#include <cassert>
#include <cstring>

const int V_MAX = 10000;
const int E_MAX = 200000;

struct RealEdge
{
	int to;
	RealEdge *next;
} *realBegin[V_MAX];

struct FakeEdge
{
	int to, org;
	bool marked;
	FakeEdge *next, *inv;
} *fakeBegin[V_MAX], *ans[V_MAX];

int realDgr[V_MAX], fakeDgr[V_MAX], belong[V_MAX];
bool used[V_MAX], vis[V_MAX];
int nv, ne, nfv, top;

void addRealEdge(int u, int v)
{
	static RealEdge edge[E_MAX];
	static int edgeCnt = 0;
	RealEdge *e = &edge[edgeCnt ++];
	e->to = v, e->next = realBegin[u];
	realBegin[u] = e;
}

FakeEdge *makeFakeEdge(int u, int v, int vOrg)
{
	static FakeEdge edge[E_MAX];
	static int edgeCnt = 0;
	FakeEdge *e = &edge[edgeCnt ++];
	e->to = v, e->next = fakeBegin[u], e->org = vOrg;
	e->marked = false;
	return fakeBegin[u] = e;
}

void addFakeEdge(int u, int v, int uOrg, int vOrg)
{
	FakeEdge *e1 = makeFakeEdge(u, v, vOrg),
			 *e2 = makeFakeEdge(v, u, uOrg);
	e1->inv = e2, e2->inv = e1;
	fakeDgr[u] ++, fakeDgr[v] ++;
}

void dfs(int u)
{
	for(FakeEdge *e = fakeBegin[u]; e; e = e->next)
	{
		int v = e->to;
		if(!e->marked)
		{
			e->marked = e->inv->marked = true;
			dfs(v);
			ans[top ++] = e;
		}
	}
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
	for(int i = 0; i < nv; i ++)
		if(realDgr[i] == 2)
		{
			int v1 = belong[realBegin[i]->to],
				v2 = belong[realBegin[i]->next->to],
				u = belong[i];
			addFakeEdge(u, v1, i, realBegin[i]->to);
			addFakeEdge(u, v2, i, realBegin[i]->next->to);
		}
	int oddCnt = 0;
	for(int i = 0; i < nfv; i ++)
		if(fakeDgr[i] % 2 == 1)
		{
			oddCnt ++;
		}
	if(oddCnt > 1)
	{
		printf("-1\n");
		return 0;
	}
	dfs(belong[0]);
	while(top)
	{
		FakeEdge *fe = ans[-- top];
		if(!used[fe->inv->org])
			printf("%d ", fe->inv->org + 1), used[fe->inv->org] = true;
		if(!used[fe->org])
			printf("%d ", fe->org + 1), used[fe->org] = true;
	}

	for(int i = 0; i < nv; i ++)
		assert(used[i]);
}
