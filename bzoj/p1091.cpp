#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef double val_t;

struct Point
{
	val_t x, y;
	Point(val_t _x = 0, val_t _y = 0):
		x(_x), y(_y){}
};

struct Line
{
	val_t a, b, c;
	inline bool suit(const Point &p) const
	{
		return a * p.x + b * p.y + c >= 0;
	}
	Line(const Point &p1, const Point &p2, const Point &p3)
	{
		a = p1.y - p2.y;
		b = - (p1.x - p2.x);
		c = - a * p1.x - b * p1.y;
		if(!suit(p3))
			a *= -1, b *= -1, c *= -1;
	}
};

inline Point intersect(const Point &p1, const Point &p2, const Line &l)
{
	double u = fabs(l.a * p1.x + l.b * p1.y + l.c),
		   v = fabs(l.a * p2.x + l.b * p2.y + l.c);
	return Point((v * p1.x + u * p2.x) / (u + v), (v * p1.y + u * p2.y) / (u + v));
}

struct Polygon
{
	vector<Point> vp;
	val_t cut(const Line &l)
	{
		static vector<Point> backup, sol;
		backup.clear(); sol.clear();
		int np = (int)vp.size();
		for(int i = 0; i < np; i ++)
		{
			Point now = vp[i], next = vp[(i + 1) % np];
			if(l.suit(now))
			{
				backup.push_back(now);
				if(!l.suit(next))
				{
					Point p = intersect(now, next, l);
					backup.push_back(p);
					sol.push_back(p);
				}
			}
			else
				if(l.suit(next))
				{
					Point p = intersect(now, next, l);
					backup.push_back(p);
					sol.push_back(p);
				}
		}
		vp = backup;
		assert(sol.size() == 2);
#define SQR(x) ((x) * (x))
		return sqrt(SQR(sol[0].x - sol[1].x) + SQR(sol[0].y - sol[1].y));
	}
};

int a, b, n, perm[8];
Point pnt[8];

double solve()
{
	static Polygon poly;
	poly.vp.clear();
	poly.vp.push_back(Point(0, 0));
	poly.vp.push_back(Point(0, b));
	poly.vp.push_back(Point(a, b));
	poly.vp.push_back(Point(a, 0));
	double res = 0;
	for(int i = 0; i < n; i ++)
		res += poly.cut(Line(pnt[perm[i]], pnt[(perm[i] + 1) % n], pnt[(perm[i] + 2) % n]));
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &a, &b);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		perm[i]= i;
	for(int i = 0; i < n; i ++)
		scanf("%lf%lf", &pnt[i].x, &pnt[i].y);
	double ans = 10E100;
	do
	{
		ans = min(ans, solve());
	} while(next_permutation(perm, perm + n));
	printf("%.3lf\n", ans);
}
