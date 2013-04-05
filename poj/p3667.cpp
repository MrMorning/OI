#include <cstdio>
#define MAXN 100010
#define INF 0x3f3f3f3f
struct Node
{
	int maxl, maxs, maxr, maxstart;
	int l, r, tag, size;
	bool marked;
} tree[MAXN * 4];
int n, m;

inline int max(int a,int b)
{return a>b?a:b;}
inline int min(int a,int b)
{return a<b?a:b;}

void Update(int i)
{
	Node &x = tree[i], &lch = tree[i * 2], &rch = tree[i * 2 + 1];
	x.maxl = lch.maxl;
	if(lch.maxl == lch.size)
		x.maxl = max(x.maxl, lch.size + rch.maxl);
	x.maxr = rch.maxr;
	if(rch.maxr == rch.size)
		x.maxr = max(x.maxr, rch.size + lch.maxr);
	x.maxs = lch.maxs, x.maxstart = lch.maxstart;
	int tmp = lch.maxr + rch.maxl;
	if(tmp > x.maxs)
		x.maxs = tmp, x.maxstart =lch.r - lch.maxr + 1;
	if(rch.maxs > x.maxs)
		x.maxs = rch.maxs, x.maxstart = rch.maxstart;
}
void Build(int i, int l, int r)
{
	tree[i].l =l, tree[i].r = r;
	tree[i].size = r - l + 1;
	if(l == r)
	{
		tree[i].maxl = tree[i].maxr = tree[i].maxs = 1;
		tree[i].maxstart = l;
		tree[i].tag = 1;
		tree[i].marked = 0;
		return;
	}
	Build(i * 2, l, (l + r) / 2);
	Build(i * 2 + 1, (l + r) / 2 + 1, r);
	Update(i);
}


void Mark(int i, int val)
{
	tree[i].maxl = tree[i].maxs = tree[i].maxr = val * tree[i].size;
	if(val)
		tree[i].maxstart = tree[i].l;
	else
		tree[i].maxstart = INF;
	tree[i].marked = true;
	tree[i].tag = val;
}

void Push_Down(int i)
{
	if(tree[i].marked)
	{
		Mark(i * 2, tree[i].tag), Mark(i * 2 + 1, tree[i].tag);
		tree[i].marked = false;
	}
}

void Change(int i, int l, int r, int a, int b, int val)
{
	if(l > b || r < a) return;
	if(a <= l && r <= b)
	{
		Mark(i, val);
		return;
	}
	Push_Down(i);
	Change(i * 2, l, (l + r)/2, a, b, val);
	Change(i * 2 + 1, (l + r)/2 + 1, r, a, b, val);
	Update(i);
}

int Ask(int i, int l, int r, int a, int b, int c)//c is the capacy
{
	if(l > b || r < a) return INF;
	if(tree[i].maxs < c) return INF;
	Push_Down(i);
	if(tree[i * 2].maxs >= c)
		return Ask(i * 2, l, (l + r) / 2, a, b, c);
	else
		if(tree[i * 2].maxr + tree[i * 2 + 1].maxl >= c)
			return tree[i * 2].r - tree[i * 2].maxr + 1;
		else
		return Ask(i * 2 + 1, (l + r) / 2 + 1, r, a, b, c);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	Build(1, 1, n);
	for(int i = 1, a, b, c, ctrl; i <= m; i ++)
	{
		scanf("%d", &ctrl);
		if(ctrl == 1)
		{
			scanf("%d\n", &c);
			a = Ask(1, 1, n, 1, n, c);
			if(a == INF)
			{
				printf("0\n");
				continue;
			}
			printf("%d\n", a);
			b = a + c - 1;
			Change(1, 1, n, a, b, 0);
		}
		else
		{
			scanf("%d %d\n", &a, &b);
			b = a + b - 1;
			Change(1, 1, n, a, b, 1);
		}
	}
}

