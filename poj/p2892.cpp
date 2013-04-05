#include <cstdio>
#define MAXN 50010
struct Node
{
	int l, r, maxl, maxr, size;
} node[MAXN << 2];

int n, m;
int stack[MAXN], top = 0;

inline int max(int a, int b)
{return a > b ? a : b;}

void Update(int i)
{
	Node &lch = node[i * 2], &rch = node[i * 2 + 1];
	node[i].maxl = lch.maxl;
	if(lch.maxl == lch.size)
		node[i].maxl += rch.maxl;
	node[i].maxr = rch.maxr;
	if(rch.maxr == rch.size)
		node[i].maxr += lch.maxr;
}

void Build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	node[i].maxl = node[i].maxr = 1;
	node[i].size = r - l + 1;
	if(l == r) return;
	Build(i * 2, l, (l + r) / 2);
	Build(i * 2 + 1, (l + r) / 2 + 1, r);
	Update(i);
}

void Change(int i, int x, int val)
{
	if(node[i].l > x || node[i].r < x) return;
	if(node[i].l == node[i].r && node[i].l == x)
	{
		node[i].maxl = node[i].maxr = val;
		return;
	}
	Change(i * 2, x, val), Change(i * 2 + 1, x, val);
	Update(i);
}

int Query(int i, int x)
{
	if(node[i].l > x || node[i].r < x) return 0;
	if(node[i].l + node[i].maxl - 1 >= x || node[i].r - node[i].maxr + 1 <= x)
	{
		if(node[i].l + node[i].maxl - 1 >= x)
			return node[i].maxl;
		else
			return node[i].maxr;
	}	
	if(node[i].l < node[i].r)
	{
		Node &lch = node[i * 2], &rch = node[i * 2 + 1];
		if(lch.r - lch.maxr + 1 <= x && x <= rch.l + rch.maxl - 1)
			return lch.maxr + rch.maxl;
		else
			return max(Query(i * 2, x), Query(i * 2 + 1, x));
	}
	return 0;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	Build(1, 1, n);
	while(m --)
	{
		char ctrl;
		int x;
		scanf("%c", &ctrl);
		if(ctrl != 'R')
		{
			scanf("%d", &x);
			if(ctrl == 'D')
			{
				Change(1, x, 0);
				stack[++ top] = x;
			}
			else
				printf("%d\n", Query(1, x));
		}
		else
		{
			x = stack[top --];
			Change(1, x, 1);
		}
		scanf("\n");
	}
}

