#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MAXN 10010
struct Node
{
	int l, r, len, cover, tag;
} node[MAXN * 20];

struct Segment
{
	int s, t, h;
} seg[2][2][MAXN];
int n;

inline int min(int a, int b)
{return a<b?a:b;}

void Build(int i, int l, int r)
{
	if(l == r)
		return;
	node[i].l = l, node[i].r = r, node[i].len = node[i].cover = node[i].tag = 0;
	if(l + 1 < r)
	{
		Build(i * 2, l, (l + r) / 2);
		Build(i * 2 + 1, (l + r) / 2, r);
	}
}

/*void Push_Down(int i)
{
	if(node[i].tag != 0)
	{
		node[i*2].cover += node[i].tag;
		node[i*2+1].cover += node[i].tag;
		node[i*2].tag = node[i*2+1].tag = node[i].tag;
		node[i].tag = 0;
	}
}*/

void Change(int i, int a, int b, int val)
{
	if(node[i].l > b || a > node[i].r)
		return;
	if(a <= node[i].l && node[i].r <= b)
	{
		//node[i].tag += val;
		node[i].cover += val;
		if (node[i].cover > 0)
			node[i].len = node[i].r - node[i].l;
		else if(node[i].l < node[i].r)
			node[i].len = node[i*2].len + node[i*2+1].len;
		else
			node[i].len = 0;
		return;
	}
	//Push_Down(i);
	if(node[i].l + 1 < node[i].r)
	{
		Change(i * 2, a, b, val);
		Change(i * 2 + 1, a, b, val);
	}
	//node[i].cover = min(node[i*2].cover, node[i*2+1].cover);
	if(node[i].cover > 0)
		node[i].len = node[i].r - node[i].l;
	else
		node[i].len = node[i * 2].len + node[i * 2 + 1].len;
}

int comp(const void *a, const void *b)
{return ((Segment*)a)->h - ((Segment*)b)->h;}

int solve(int t)
{
	qsort(seg[t][0] + 1, n, sizeof(Segment), comp);
	qsort(seg[t][1] + 1, n, sizeof(Segment), comp);
	int in_p = 1, out_p = 1, ans = 0;
	memset(node, 0, sizeof(node));
	Build(1, 0, 20000);
	int pre = 0;
	for(int i = 0; i < 20000; i ++)
	{
		while(seg[t][0][in_p].h == i && in_p <= n)
		{
			Change(1, seg[t][0][in_p].s, seg[t][0][in_p].t, 1), in_p ++;
			ans += abs(node[1].len - pre);
			pre = node[1].len;
		}
		while(seg[t][1][out_p].h == i && out_p <= n)
		{
			Change(1, seg[t][1][out_p].s, seg[t][1][out_p].t, -1), out_p ++;
			ans += abs(node[1].len - pre);
			pre = node[1].len;
		}
	}
	return ans;
}

void debug()
{
	for(int i = 1; i <= MAXN * 20 - 1; i ++)
		if(node[i].len != 0 || node[i].cover != 0)
			printf("node: %d l: %d, r: %d, len: %d, cover: %d\n", i,node[i].l, node[i].r, node[i].len, node[i].cover);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1, x1, y1, x2, y2; i <= n; i ++)
	{
		scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
		x1 += 10000, y1 += 10000, x2 += 10000, y2 += 10000;
		seg[0][0][i].s = x1, seg[0][0][i].t = x2, seg[0][0][i].h = y1;
		seg[0][1][i].s = x1, seg[0][1][i].t = x2, seg[0][1][i].h = y2;
		seg[1][0][i].s = y1, seg[1][0][i].t = y2, seg[1][0][i].h = x1;
		seg[1][1][i].s = y1, seg[1][1][i].t = y2, seg[1][1][i].h = x2;
	}
	printf("%d\n", (solve(0) + solve(1)));
}
