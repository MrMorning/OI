#include <cstdio>
#define MAXN 33010

int parent[MAXN], size[MAXN], dist[MAXN];
int n, m;

void Make_Set(int x)
{
	parent[x] = x;
	size[x] = 1;
	dist[x] = 0;
}

int Find_Set(int x)
{
	if(x != parent[x])
	{
		int tmp = parent[x];
		parent[x] = Find_Set(parent[x]);
		dist[x] += dist[tmp];
	}
	return parent[x];
}

void Merge(int x, int y)
{
	x = Find_Set(x), y = Find_Set(y);
	if(x == y) return;
	parent[x] = y;
	dist[x] = size[y];
	size[y] += size[x];
}

int main()
{
	freopen("t.in","r",stdin);
	scanf("%d", &m);
	int n = MAXN;
	for(int i = 1; i <= n; i ++) Make_Set(i);
	for(int i = 1; i <= m; i ++)
	{
		int a, b;
		char ctrl;
		scanf("\n%c %d", &ctrl, &a);
		if(ctrl == 'M') scanf("%d", &b);
		if(ctrl == 'M')
			Merge(a, b);
		else
		{
			Find_Set(a);
			printf("%d\n", dist[a]);
		}
	}
}
