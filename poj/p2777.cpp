#include <cstdio>
#include <algorithm>
#define MAXN 100010 * 4

using namespace std;

int Count_Bit(int x)
{
	x = (x & 0x55555555) + (x >> 1 & 0x55555555);
	x = (x & 0x33333333) + (x >> 2 & 0x33333333);
	x = (x & 0x0F0F0F0F) + (x >> 4 & 0x0F0F0F0F);
	x = (x & 0x00FF00FF) + (x >> 8 & 0x00FF00FF);
	x = (x & 0x0000FFFF) + (x >> 16 & 0x0000FFFF);
	return(x);
}

struct Node
{
	int color, tag, l, r;
	bool e, marked;
	Node(bool c = true):e(c)
	{
		marked = false; color = tag = 0;
	}
} T[MAXN];

Node operator+(const Node &L, const Node &R)
{
	if(! L.e) return R; if(! R.e) return L;
	Node F;
	F.l = L.l, F.r = R.r;
	F.color = L.color | R.color;
	return F;
}

void Push_Down(int x)
{
	if(T[x].marked)
	{
		T[x*2].color = T[x*2].tag = T[x].tag;
		T[x*2+1].color = T[x*2+1].tag = T[x].tag;
		T[x*2].marked = T[x*2+1].marked = true;
		T[x].marked = false;
	}
}

void Build(int x, int l, int r)
{
	T[x].l = l, T[x].r = r;
	if(l == r)
	{
		T[x].color = 1;
		return;
	}	
	int mid = (l + r) / 2;
	Build(x*2, l, mid), Build(x*2+1, mid + 1, r);
	T[x] = T[x*2] + T[x*2+1];
}

void Change(int x, int a, int b, int c)
{
	if(T[x].l > b || T[x].r < a) return;
	if(a <= T[x].l && T[x].r <= b)
	{
		T[x].color = c, T[x].marked = true;
		T[x].tag = c;
		return;
	}
	Push_Down(x);
	Change(x*2, a, b, c), Change(x*2+1, a, b, c);
	T[x] = T[x*2] + T[x*2+1];
}

Node Ask(int x, int a, int b)
{
	if(T[x].l > b || T[x].r < a) return Node(false);
	if(a <= T[x].l && T[x].r <= b) return T[x];
	Push_Down(x);
	return Ask(x*2, a, b) + Ask(x*2+1, a, b);
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, colornum, m;
	scanf("%d %d %d\n", &n, &colornum, &m);
	Build(1, 1, n);
	for(int i = 1, a, b, c; i <= m; i ++)
	{
		char ctrl;
		scanf("\n%c %d %d", &ctrl, &a, &b);
		if(a > b) swap(a, b);
		if(ctrl == 'C')
		{
			scanf("%d",&c);
			c = 1 << (c-1);
			Change(1, a, b, c);
		}
		else
		{
			Node t = Ask(1, a, b);
			int tmp = t.color;
			printf("%d\n", Count_Bit(tmp));
		}
	}
}
