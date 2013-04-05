#include <cstdio>
#define MAXN 50100
int n, k;
int parent[MAXN], relation[MAXN];
int cnt = 0;

void Make_Set(int x)
{
	parent[x] = x, relation[x] = 0;
}

int Find_Set(int x)
{
	int tmp;
	if(x != parent[x])
	{
		tmp = parent[x];
		parent[x] = Find_Set(parent[x]);
		relation[x] = (relation[x] + relation[tmp]) % 3;
	}
	return parent[x];
}

void Union(int x, int y, int d)
{
	int p = Find_Set(x), q = Find_Set(y);
	parent[p] = q;
	relation[p] = (relation[y] - relation[x] + d + 2) % 3;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n",&n,&k);
	for(int i = 1; i <= n; i ++) Make_Set(i);
	for(int i = 1, d, x, y; i <= k; i ++)
	{
		scanf("%d %d %d\n",&d,&x,&y);
		if(x > n || y > n || (d == 2 && x == y))
		{
			cnt ++;
			continue;
		}
		int p = Find_Set(x), q = Find_Set(y);
		if(p != q)
			Union(x, y, d);
		else
			if((relation[y] + d + 2) % 3 != relation[x]) cnt ++;
	}
	printf("%d\n",cnt);
}
