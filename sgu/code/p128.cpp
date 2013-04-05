#include <cstdio>
#include <algorithm>
using namespace std;
const int RANGE = 20010;
const int N_MAX = 10000;
int idt[RANGE + 1];

struct Point
{
	int x, y, flag, dep, to[2], idx;
} p[N_MAX];
int np;
bool vis[N_MAX];
int ans;

#define IN 0
#define OUT 1

bool cmp_x(const Point &p1, const Point &p2)
{
	return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool cmp_y(const Point &p1, const Point &p2)
{
	return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

bool cmp_idx(const Point &p1, const Point &p2)
{
	return p1.idx < p2.idx;
}

inline int lowbit(int i)
{
	return i & (-i);
}

int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += idt[i];
	return res;
}

void add(int x, int y)
{
	for(int i = x; i <= RANGE; i += lowbit(i))
		idt[i] += y;
}

void noSol()
{
	printf("0\n");
	exit(0);
}

void dfs(int u)
{
	vis[u] = true;
	for(int t = 0; t < 2; t ++)
		if(!vis[p[u].to[t]])
			dfs(p[u].to[t]);
}
void solve() {
	for(int i = 0; i < np; i ++)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].x += 10001, p[i].y += 10001;
		p[i].idx = i;
	}
	sort(p, p + np, cmp_x);
	for(int i = 0; i < np; i ++)
	{
		int st = i;
		while(i + 1 < np && p[i + 1].x == p[st].x)
			i ++;
		int len = i - st + 1;
		if(len & 1)
			noSol();
		for(int j = st; j <= i; j += 2)
		{
			ans += p[j + 1].y - p[j].y;
			p[j].to[0] = p[j + 1].idx; p[j + 1].to[0] = p[j].idx;
			p[j].flag = IN;
			p[j + 1].flag = OUT;
		}
	}

	sort(p, p + np, cmp_y);
	for(int i = 0; i < np; i ++)
	{
		int st = i;
		while(i + 1 < np && p[i + 1].y == p[st].y)
			i ++;
		int len = i - st + 1;
		if(len & 1)
			noSol();
		for(int j = st; j <= i; j += 2)
		{
			ans += p[j + 1].x - p[j].x;
			p[j].to[1] = p[j + 1].idx; p[j + 1].to[1] = p[j].idx;
			if(p[j].flag == OUT)
				p[j].dep = sum(p[j].x);
			if(p[j + 1].flag == OUT)
				p[j + 1].dep = sum(p[j + 1].x);
			add(p[j].x, 1); add(p[j + 1].x + 1, -1);
			if(p[j].flag == IN)
				p[j].dep = sum(p[j].x);
			if(p[j + 1].flag == IN)
				p[j + 1].dep = sum(p[j + 1].x);
		}
	}

	sort(p, p + np, cmp_x);
	for(int i = 0; i < np; i ++)
	{
		int st = i;
		while(i + 1 < np && p[i + 1].x == p[st].x)
			i ++;
		for(int j = st; j <= i; j += 2)
			if(p[j].dep != p[j + 1].dep)
				noSol();
	}

	sort(p, p + np, cmp_idx);
	dfs(0);
	for(int i = 0; i < np; i ++)
		if(!vis[i])
			noSol();
	printf("%d\n", ans);
}
int main()
{
	freopen("t.in", "r", stdin);
	while (scanf("%d", &np) != EOF)
		solve();
}
