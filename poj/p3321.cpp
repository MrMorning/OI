#include <cstdio>
#define MAXN 200010

int count, next[MAXN], begin[MAXN], end[MAXN];
int start[MAXN * 2], over[MAXN * 2];
int tree[MAXN * 2];
int time = 0, n, m;
bool vis[MAXN], exist[MAXN * 2];

void Add_Edge(int a, int b)
{
	count ++;
	next[count] = begin[a];
	begin[a] = count;
	end[count] = b;
}

void dfs(int x)
{
	vis[x] = true;
	start[x] = ++ time;
	for(int now = begin[x]; now; now = next[now])
	{
		int u = end[now];
		if(!vis[u])
			dfs(u);
	}	
	over[x] = ++time;
}

inline int lowbit(int x)
{return x & (-x);}

void Update(int x, int v)
{
	if (x == 0) return;
	while(x <= MAXN)
	{
		tree[x] += v;
		x += lowbit(x);
	}
}

int Sum(int x)
{
	int cnt = 0;
	while(x > 0)
	{
		cnt += tree[x];
		x -= lowbit(x);
	}
	return cnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1, a, b; i < n; i ++)
	{
		scanf("%d %d\n", &a, &b);
		Add_Edge(a, b);
		Add_Edge(b, a);
	}
	dfs(1);
	for(int i = 1; i <= n; i ++)
		Update(start[i], exist[start[i]] ^= 1);
	scanf("%d\n", &m);
	while(m --)
	{
		char ctrl;
		int x;
		scanf("%c %d\n", &ctrl, &x);
		if(ctrl == 'C')
		{
			int v;
			exist[start[x]] ^= 1;
			if(exist[start[x]]) v = 1;
			else v = -1;
			Update(start[x], v);
		}
		else
			printf("%d\n", Sum(over[x]) - Sum(start[x] - 1));
	}
}
