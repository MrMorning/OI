#include <cstdio>
#include <cstring>
#include <cmath>
#define MAXN 10010
#define EPS 10E-6

double sin_hash[721], cos_hash[721];
const double PI = 3.141592654;

struct Point_t
{
	double x, y;
	Point_t(){};
	Point_t(double _x, double _y): x(_x), y(_y){};
} point[MAXN];

Point_t operator+ (const Point_t &a, const Point_t &b)
{
	return Point_t(a.x + b.x, a.y + b.y);
}
Point_t operator- (const Point_t &a, const Point_t &b)
{
	return Point_t(a.x - b.x, a.y - b.y);
}

struct Node_t
{
	int l, r, tagDgr;
	Point_t s, e;
	void rotate(int dgr)
	{
		e = e - s;
		double x2 = cos_hash[dgr] * e.x - sin_hash[dgr] * e.y;
		double y2 = sin_hash[dgr] * e.x + cos_hash[dgr] * e.y;
		e.x = s.x + x2, e.y = s.y + y2;
	}
} node[MAXN << 2];
int angle[MAXN];

void update(int i);

void build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r, node[i].tagDgr = 0;
	node[i].s = point[l - 1], node[i].e = point[r];
	if(l < r)
	{
		build(i * 2, l, (l + r) / 2);
	   	build(i * 2 + 1, (l + r) / 2 + 1, r);
		update(i);
	}
}

void mark(int i, int dgr)
{
	node[i].rotate(dgr), node[i].tagDgr = (dgr + node[i].tagDgr) % 360;
}

void pushDown(int i)
{
	if(node[i].tagDgr)
	{
		mark(i * 2, node[i].tagDgr), mark(i * 2 + 1, node[i].tagDgr);
		node[i].tagDgr = 0;
	}
}

void update(int i)
{
	Node_t &x = node[i], &lch = node[i * 2], &rch = node[i * 2 + 1];
	x.e = x.s + (lch.e - lch.s) + (rch.e - rch.s);
}

void change(int i, int l, int r, int dgr)
{
	Node_t &x = node[i];
	if(x.l > r || x.r < l)
		return;
	if(l <= x.l && x.r <= r)
	{
		mark(i, dgr);
		return;
	}
	pushDown(i);
	change(i * 2, l, r, dgr);
   	change(i * 2 + 1, l, r, dgr);
	update(i);
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	for(int dgr = 0; dgr <= 720; dgr ++)
	{
		sin_hash[dgr] = sin(PI / 180 * dgr);
		cos_hash[dgr] = cos(PI / 180 * dgr);
	}
	int n, c;
	bool first = false;
	while(~scanf("%d%d", &n, &c))
	{
		if(first)
			printf("\n");
		first = true;
		int cnt = 0;
		for(int i = 1; i <= n; i ++)
		{
			int ty;
			scanf("%d", &ty);
			cnt += ty;
			point[i].x = 0, point[i].y = cnt;
			angle[i - 1] = 180;
		}
		build(1, 1, n);
		for(int i = 1; i <= c; i ++)
		{
			int t1, t2;
			scanf("%d%d", &t1, &t2);
			int delta = t2 - angle[t1] + 360;
			angle[t1] = t2;
			change(1, t1 + 1, n, delta);
			printf("%.2lf %.2lf\n", node[1].e.x + EPS, node[1].e.y + EPS);
		}
	}
}
