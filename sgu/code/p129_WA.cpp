#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

const int N_MAX = 401;
const double EPS = 10e-8;

struct Point
{
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
} p[N_MAX];

struct Point_f
{
	double x, y;
	Point_f(){}
	Point_f(double _x, double _y):
		x(_x), y(_y){}
	bool operator <(const Point_f &t) const
	{
		return x < t.x || (fabs(x - t.x) < EPS && y < t.y);
	}
	bool operator== (const Point_f &t) const
	{
		return fabs(x - t.x) < EPS && fabs(y - t.y) < EPS;
	}
};
int np;

#define SQR(x) ((x) * (x))
#define DIST(a, b) (sqrt(SQR((a).x - (b).x) + SQR((a).y - (b).y)))

inline Point operator- (const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

inline int cross(const Point &p1, const Point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

inline bool cmp(const Point &p1, const Point &p2)
{
	return cross(p2 - p[0], p1 - p[0]) > 0;
}

bool inside(const Point &pi)
{
	for(int i = 0; i < np; i ++)
		if(cross(p[i + 1] - pi, p[i] - pi) <= 0)
			return false;
	return true;
}

inline bool intersect(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
	int pl = min(p1.x, p2.x), pr = max(p1.x, p2.x),
		pu = max(p1.y, p2.y), pd = min(p1.y, p2.y);
	int ql = min(q1.x, q2.x), qr = max(q1.x, q2.x),
		qu = max(q1.y, q2.y), qd = min(q1.y, q2.y);
	if(pl > qr || pr < ql)
		return false;
	if(pd > qu || pu < qd)
		return false;
	if(cross(p1 - q1, q2 - q1) * cross(q2 - q1, p2 - q1) >= 0)
		if(cross(q1 - p1, p2 - p1) * cross(p2 - p1, q2 - p1) >= 0)
			return true;
	return false;
}
inline Point_f getIntersect(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
	int a = q2.y - q1.y,
		b = q1.x - q2.x,
		c = -(a * q1.x + b * q1.y);
	double u = fabs(a * p1.x + b * p1.y + c),
		   v = fabs(a * p2.x + b * p2.y + c);
	return Point_f((v * p1.x + u * p2.x) / (u + v), (v * p1.y + u * p2.y) / (u + v));
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &np);
	for(int i = 0; i < np; i ++)
		scanf("%d%d", &p[i].x, &p[i].y);
	sort(p + 1, p + np, cmp);
	p[np] = p[0];
	int m;
	scanf("%d", &m);
	while(m --)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		Point p1(x1, y1), p2(x2, y2);

		bool onSeg = false;
		for(int i = 0; i < np; i ++)
			if(intersect(p[i], p[i + 1], p1, p2) && cross(p[i] - p[i + 1], p1 - p2) == 0)
			{
				onSeg = true;
				break;
			}
		if(onSeg)
		{
			printf("0.00\n");
			continue;
		}
		bool b1 = inside(p1), b2 = inside(p2);
		if(b1 && b2)
			printf("%.2lf\n", DIST(p1, p2));
		else if(!b1 && !b2)
		{
			static vector<Point_f> vp;
			vp.clear();
			for(int i = 0; i < np; i ++)
				if(intersect(p[i], p[i + 1], p1, p2))
					vp.push_back(getIntersect(p[i], p[i + 1], p1, p2));
			if(vp.size() == 0)
				printf("0.00\n");
			else
			{
				sort(vp.begin(), vp.end());
				vector<Point_f>::iterator it = unique(vp.begin(), vp.end());
				vp.resize(it - vp.begin());
				assert(vp.size() <= 2);
				if(vp.size() == 1)
					printf("0.00\n");
				else
					printf("%.2lf\n", DIST(vp[0], vp[1]));
			}
		}
		else 
		{
			if(b2)
				swap(p1, p2);
			bool suc = false;
			for(int i = 0; i < np; i ++)
				if(intersect(p[i], p[i + 1], p1, p2))
				{
					Point_f pt = getIntersect(p[i], p[i + 1], p1, p2);
					double res = DIST(p1, pt);
					if(fabs(res) > EPS)
					{
						suc = true;
						printf("%.2lf\n", res);
						break;
					}
				}
			if(!suc)
				printf("0.00\n");
		}
	}
}
