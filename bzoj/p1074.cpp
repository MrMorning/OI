#include <cstdio>
#include <cmath>
#include <vector>
#define foreach(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)
using namespace std;

struct Point
{
	double x, y;
	Point(double _x = 0, double _y = 0):
		x(_x), y(_y){}
};

Point operator- (const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

double cross(const Point &p1, const Point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

struct Line
{
	Point from, to;
	double a, b, c;
	Line(){}
	Line(const Point &_from, const Point &_to):
		from(_from), to(_to)
	{
		Point nrm = to - from;
		a = nrm.y, b = - nrm.x;
		c = - (a * to.x + b * to.y);
	}
	double f(const Point &p) const
	{
		return a * p.x + b * p.y + c;
	}
};

struct Polygon
{
	vector<Point> vp;
	void cut(const Line &l, vector<Point> &output);
	bool contain(const Point &p);
};

vector<Polygon> poly_vec;
int n_oprt, n_hole;

inline Point symmetry(const Line &l, const Point &p)
{
	double u = l.f(p), v = l.a * l.a + l.b * l.b;
	return Point(p.x - 2 * l.a * u / v, p.y - 2 * l.b * u / v);
}

inline Point intersect(const Line &l, const Point &p1, const Point &p2)
{
	double u = fabs(l.f(p1)), v = fabs(l.f(p2));
	return Point((p1.x * v + p2.x * u) / (u + v), (p1.y * v + p2.y * u) / (u + v));
}

void Polygon::cut(const Line &l, vector<Point> &output)
{
	static vector<Point> vq;
	vq.clear();
	int np = (int)vp.size();
	for(int i = 0; i < np; i ++)
		if(cross(l.to - l.from, vp[i] - l.from) <= 0)
		{
			output.push_back(vp[i]);
			if(cross(l.to - l.from, vp[(i + 1) % np] - l.from) > 0)
			{
				Point tmp = intersect(l, vp[i], vp[(i + 1) % np]);
				vq.push_back(tmp); 
				if(cross(l.to - l.from, vp[i] - l.from) != 0)
					output.push_back(tmp);
			}
		}
		else
		{
			vq.push_back(vp[i]);
			if(cross(l.to - l.from, vp[(i + 1) % np] - l.from) <= 0)
			{
				Point tmp = intersect(l, vp[i], vp[(i + 1) % np]);
				vq.push_back(tmp); 
				if(cross(l.to - l.from, vp[(i + 1) % np] - l.from) != 0)
					output.push_back(tmp);
			}
		}
	vp = vq;
}

bool Polygon::contain(const Point &p)
{
	int np = (int)vp.size();
	for(int i = 0; i < np; i ++)
		if(cross(vp[(i + 1) % np] - vp[i], p - vp[i]) >= 0)
			return false;
	return true;
}

void debug(const Polygon &poly)
{
	for(vector<Point>::const_iterator it = poly.vp.begin(); it != poly.vp.end(); it ++)
		printf("%.2lf %.2lf\n", it->x, it->y);
	printf("***********************************************\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	Polygon init_poly;
	init_poly.vp.push_back(Point(0, 0));
	init_poly.vp.push_back(Point(0, 100));
	init_poly.vp.push_back(Point(100, 100));
	init_poly.vp.push_back(Point(100, 0));

	poly_vec.push_back(init_poly);

	scanf("%d", &n_oprt);
	while(n_oprt --)
	{
		static Point p1, p2;
		static Line l;
		static vector<Point> pnt_vec;
		static vector<Polygon> poly_buf;

		scanf("%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y);
		l = Line(p1, p2);
		poly_buf.clear();
		foreach(it, poly_vec)
		{
			pnt_vec.clear();
			it->cut(l, pnt_vec);
			if(pnt_vec.size() == 0)
				continue;
			static Polygon poly_new;
			poly_new.vp.clear();
			for(vector<Point>::reverse_iterator it = pnt_vec.rbegin(); it != pnt_vec.rend(); it ++)
				poly_new.vp.push_back(symmetry(l, *it));
			poly_buf.push_back(poly_new);
		}
		foreach(it, poly_buf)
			poly_vec.push_back(*it);
	}
//	debug(poly_vec[0]);
//	debug(poly_vec[1]);
//	debug(poly_vec[2]);
//	debug(poly_vec[3]);


	scanf("%d", &n_hole);
	while(n_hole --)
	{
		static Point hole;
		scanf("%lf%lf", &hole.x, &hole.y);
		int ans = 0;
		foreach(it, poly_vec)
			if(it->contain(hole))
				ans ++;
		printf("%d\n", ans);
	}
}
