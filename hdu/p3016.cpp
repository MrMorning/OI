#include <cstdio>
#include <algorithm>
#define MAXN 100100
#define INF 0x3f3f3f3f

using namespace std;

struct Node
{
	int l, r, color;
} node[MAXN << 2];

struct Stuff
{
	int h, dl, dr, xl, xr, value;
	bool operator< (const Stuff &a)const
	{
		return h < a.h;
	}
} blank[MAXN];

int n, m, f[MAXN];

void Build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	node[i].color = 0;
	if(l == r) return;
	Build(i * 2, l, (l + r) / 2);
	Build(i * 2 + 1, (l + r) / 2 + 1, r);
}

void Push_Down(int i)
{
	if(node[i].color != -1)
		node[i * 2].color = node[i * 2 + 1].color = node[i].color;
}

void Change(int i, int a, int b, int color)
{
	if(node[i].r < a || b < node[i].l )
		return;
	if(a <= node[i].l && node[i].r <= b)
	{
		node[i].color = color;
		return;
	}
	Push_Down(i);
	Change(i * 2, a, b, color);
	Change(i * 2 + 1, a, b, color);
	if(node[i * 2].color != node[i * 2 + 1].color)
		node[i].color = -1;
	else
		node[i].color = node[i * 2].color;
}

int Ask(int i, int x)
{
	if(node[i].r < x || node[i].l > x) return 0;
	if(node[i].l <= x && x <= node[i].r && node[i].color != -1)
		return node[i].color;
	return max(Ask(i * 2, x), Ask(i * 2 + 1, x));
}

int main()
{
	freopen("t.in", "r", stdin);
	while(! feof(stdin))
	{
		scanf("%d\n", &m);
		for(int i = 0; i < m; i ++)
			f[i] = -INF;
		f[m] = 100;
		for(int i = 1; i <= m; i ++)
			scanf("%d %d %d %d\n", &blank[i].h, &blank[i].xl, &blank[i].xr, &blank[i].value);
		sort(blank + 1, blank + m + 1);
		for(int i = 1; i <= m; i ++)
			blank[i].h = i;
		Build(1, 1, MAXN);
		for(int i = 1; i <= m; i ++)
		{
			blank[i].dl = Ask(1, blank[i].xl);
			blank[i].dr = Ask(1, blank[i].xr);
			Change(1, blank[i].xl, blank[i].xr, i);
		}
		for(int i = m; i >= 1; i --)
		{
			int tmp = f[i] + blank[i].value;
			if(tmp < 0) tmp = -INF;
			f[blank[i].dl] = max(f[blank[i].dl], tmp);
			f[blank[i].dr] = max(f[blank[i].dr], tmp);
		}
		if(f[0] > 0)
			printf("%d\n", f[0]);
		else
			printf("-1\n");
	}
}
