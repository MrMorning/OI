#include <cstdio>
#include <cstring>
#define MAXN 10010
struct Edge
{
	int next, end;
} E[MAXN];

int begin[MAXN];
int ancestor[MAXN], p[MAXN], rank[MAXN];
int inD[MAXN];
bool vis[MAXN];
int Qu, Qv, count, n;

void Add_Edge(int a,int b)
{
	count ++;
	E[count].next = begin[a];
	begin[a] = count;
	E[count].end = b;
}

void Make_Set(int u)
{
	p[u] = u; rank[u] = 0;
}

int Find_Set(int u)
{
	if(u != p[u]) p[u] = Find_Set(p[u]);
	return p[u];
}

void Union(int u, int v)
{
	u = Find_Set(u), v = Find_Set(v);
	if(u == v) return;
	if(rank[u] > rank[v]) p[v] = u;
	else
	{
		if(rank[u] == rank[v]) rank[v] ++;
		p[u] = v;
	}
}

void LCA(int u)
{
	Make_Set(u);
	ancestor[Find_Set(u)] = u;
	for(int now = begin[u]; now; now = E[now].next)
	{
		int v = E[now].end;
		LCA(v);
		Union(v, u);
		ancestor[Find_Set(u)] = u;
	}
	vis[u] = true;
	if(u == Qu && vis[Qv])
		printf("%d\n", ancestor[Find_Set(Qv)]);
	else if(u == Qv && vis[Qu])
		printf("%d\n", ancestor[Find_Set(Qu)]);
}

void solve()
{
	count = 0, memset(begin, 0 , sizeof(begin));
   	memset(vis, 0 ,sizeof(vis));
   	memset(inD, 0 ,sizeof(inD));
	scanf("%d\n", &n);
	for(int i = 1, a, b; i <= n-1; i ++)
	{
		scanf("%d %d\n", &a, &b), Add_Edge(a, b);
		inD[b] ++;
	}
	scanf("%d %d\n", &Qu, &Qv);
	for(int i = 1; i <= n; i ++)
		if(inD[i] == 0)
			LCA(i);
}

int main()
{
	freopen("t.in","r",stdin);
	int testnum;
	scanf("%d\n",&testnum);
	while(testnum --)
		solve();
}
