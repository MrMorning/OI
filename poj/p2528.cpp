#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXN 20100

struct Cache
{
	int l, r;
} cache[MAXN];

int tree[MAXN * 4];
int n, ans, X[2 * MAXN], nx;
bool hash[MAXN];
bool exist[10000003];
int map[10000003];

int comp(const void *a, const void *b)
{return *(int*)a - *(int*)b;}

void insert(int i, int l, int r, int a, int b, int color)
{
	if(l > b || a > r) return;
	//if(tree[i] != -1)
	if(a <= l && r <= b)
	{
		tree[i] = color;
		return;
	}
	if(tree[i] != -1)
	{
		tree[i * 2] = tree[i], tree[i * 2 + 1] = tree[i];
		tree[i] = -1;
	}
	//if(l + 1 < r)
	{
		insert(i * 2, l, (l + r)/2, a, b, color);
		insert(i * 2 + 1, (l + r)/2 + 1, r, a, b, color);
	}
	tree[i] = -1;
}

void ask(int i, int l, int r, int a, int b)
{
	if(l > b || a > r) return;
	if(a <= l && r <= b)
	{
		if(tree[i] != -1)
		{
			if(!hash[tree[i]])
				ans ++, hash[tree[i]] = true;
			return;
		}
	}
	//pushdown(i);
	//if(l + 1 < r)
	{
		ask(i * 2, l, (l + r)/2, a, b);
		ask(i * 2 + 1, (l + r)/2 + 1, r, a, b);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		scanf("%d\n", &n);
		memset(X, 0, sizeof(X));
		memset(exist, 0, sizeof(exist));
		nx = 0;
		for(int i = 1, a, b; i <= n; i ++)
		{
			scanf("%d %d\n", &a, &b);
			if(!exist[a])
			{
				X[++ nx] = a;
				exist[a] = true;
			}
			if(!exist[b])
			{
				X[++ nx] = b;
				exist[b] = true;
			}
			cache[i].l = a, cache[i].r = b;
		}
		qsort(X + 1, nx, sizeof(int), comp);
		for(int i = 1; i <= nx; i ++)
			map[X[i]] = i;
		memset(hash, 0, sizeof(hash));
		memset(tree, 0xff, sizeof(tree));
		for(int i = 1; i <= n; i ++)
			insert(1, 1, nx, map[cache[i].l], map[cache[i].r], i);
		ans = 0;
		ask(1, 1, nx, 1, nx);
		printf("%d\n", ans);
	}
}
