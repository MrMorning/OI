#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_PNT_MAX = 310;
const double EPS = 10E-6;
const double INF = 10E7;

struct Point
{
	double x, y;
	Point(double _x = 0, double _y = 0): x(_x), y(_y){}
};

struct Line
{
	double a, b, c;
	Line(double _a, double _b, double _c): a(_a), b(_b), c(_c){}
	Line(const Point &p1, const Point &p2)
	{
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		assert(fabs(b) >= EPS);
		c = p2.x * p1.y - p1.x * p2.y;
	}
};

Point org_pnt[N_PNT_MAX], cur_pnt[N_PNT_MAX];
int n_org, n_cur;

inline Point intersect(const Point &p1, const Point &p2, const Line &l)
{
	double u = l.a * p1.x + l.b * p1.y + l.c,
		   v = l.a * p2.x + l.b * p2.y + l.c;
	return Point(u / (u + v) * p2.x + v / (u + v) * p1.x,
			u / (u + v) * p2.y + v / (u + v) * p1.y);
}
inline double calc(const Line &l, const Point &p)
{
	return p.y + (l.a / l.b) * p.x + l.c / l.b;
}
void cut(const Line &l)
{
	static Point tmp_pnt[N_PNT_MAX];
	int n_tmp = 0;
	for(int i = 0; i < n_cur; i ++)
	{
		Point &p = cur_pnt[i];
		if(calc(l, p) >= -EPS)
			tmp_pnt[n_tmp ++] = p;
		else
		{
			Point &ins_p = cur_pnt[(i + n_cur - 1) % n_cur];
			if(calc(l, ins_p) > -EPS)
				tmp_pnt[n_tmp ++] = intersect(cur_pnt[i], ins_p, l);

			ins_p = cur_pnt[(i + 1) % n_cur];
			if(calc(l, ins_p) > -EPS)
				tmp_pnt[n_tmp ++] = intersect(cur_pnt[i], ins_p, l);
		}
	}
	memcpy(cur_pnt, tmp_pnt, sizeof(Point) * n_tmp);
	n_cur = n_tmp;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n_org);
	for(int i = 0; i < n_org; i ++)
		scanf("%lf", &org_pnt[i].x);
	for(int i = 0; i < n_org; i ++)
		scanf("%lf", &org_pnt[i].y);

	cur_pnt[0] = Point(- INF + 1, - INF);
	cur_pnt[1] = Point(- INF, INF + 1);
	cur_pnt[2] = Point(INF, INF + 1);
	cur_pnt[3] = Point(INF, - INF+ 1);
	n_cur = 4;
	for(int i = 0; i < n_org - 1; i ++)
	{
		Line l(org_pnt[i], org_pnt[i + 1]);
		cut(l);
	}

	int r = 0;
	for(int i = 1; i < n_cur; i ++)
		if(cur_pnt[i].x > cur_pnt[r].x)
			r = i;
	double ans = INF;
	for(int s = n_org - 2; s >= 0; s --)
	{	
		while(cur_pnt[r].x > org_pnt[s].x)
		{
			while(cur_pnt[r].x > org_pnt[s + 1].x)
				r = (r + 1) % n_cur;
			Line l(org_pnt[s], org_pnt[s + 1]);
			ans = MIN(ans, cur_pnt[r].y - (- l.a / l.b * cur_pnt[r].x - l.c / l.b));
			r = (r + 1) % n_cur;
		}
		Line l(cur_pnt[r], cur_pnt[(r + n_cur - 1) % n_cur]);
		ans = MIN(ans, (- l.a / l.b * org_pnt[s].x - l.c / l.b) - org_pnt[s].y);
	}
	printf("%.3lf\n", ans);
}
