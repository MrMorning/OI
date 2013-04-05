#include <cstdio>
#include <cstring>
#define MAXN 100100
#define INF 0x3f3f3f3f
int n, m, p[MAXN], rank[MAXN], ops[MAXN];

void Make_Set(int u)
{
	p[u] = u;
	rank[u] = 0;
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

void solve()
{
	memset(p, 0 ,sizeof(p)), memset(rank, 0, sizeof(rank));
	memset(ops, 0x3f ,sizeof(p));
	scanf("%d %d\n", &n, &m);
	for(int i = 1; i <= n; i ++) Make_Set(i);
	while(m --)
	{
		char ctrl;
		int a, b;
		scanf("%c %d %d\n", &ctrl, &a, &b);
		int fa = Find_Set(a);
		int fb = Find_Set(b);
		if(ctrl == 'A')
		{
			if(ops[fa] != INF && Find_Set(ops[fa]) == fb)
				printf("In different gangs.\n");
			else if(fa == fb)
				printf("In the same gang.\n");
			else
				printf("Not sure yet.\n");
		}
		else
		{
			if(ops[fa] != INF) Union(ops[fa],fb);
			else ops[fa] = fb;
			if(ops[fb] != INF) Union(ops[fb],fa);
			else ops[fb] = fa;
		}
	}

}
int main()
{
	freopen("t.in", "r", stdin);
	int testnum;
	scanf("%d\n", &testnum);
	while(testnum --)
		solve();
}
