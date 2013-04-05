#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
const int kNMax = 510;
const double kRange = 1e10;
const double kEps = 1e-6;
inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}
struct Point {
	double x, y;
	Point(){}
	Point(double xx, double yy):x(xx), y(yy){}
};
Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x+p2.x, p1.y+p2.y);
}
Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x, p1.y-p2.y);
}
Point operator* (const Point &p1, double k) {
	return Point(p1.x*k, p1.y*k);
}
double cross(const Point &p1, const Point &p2) {
	return p1.x*p2.y - p1.y*p2.x;
}
struct Line {
	double a, b, c;
	Point from, to;
	Line(Point _from, Point _to):
		from(_from), to(_to) {
			b = (to-from).x;
			a = -(to-from).y;
			c = -(from.x*a+from.y*b);
		}
	double f(const Point &p) const{
		return a*p.x+b*p.y+c;
	}	
	Point getItc(const Point &p1, const Point &p2) const{
		double u = fabs(f(p1)), v = fabs(f(p2));
		Point d = p2-p1;
		d = d * (u/(u+v));
		return p1+d;
	}
};

struct Polygon {
    vector<Point> vp;
    void cut(const Line &l);
	double calcArea() {
		double res = 0;
		int sz = vp.size();
		for ( int i = 0; i < sz; i ++ )
			res += cross(vp[i], vp[(i+1)%sz]);
		return fabs(res)/2;
	}
	void init() {
		vp = vector<Point>(4);
		vp[0] = Point(-kRange, -10);
		vp[1] = Point(kRange, -10);
		vp[2] = Point(kRange, 10);
		vp[3] = Point(-kRange, 10);
	}
} poly;

void Polygon::cut(const Line &l) {
	static vector<Point> vq;
	vq.clear();
	int sz = vp.size();
	for ( int i = 0; i < sz; i ++ ) {
		if ( sgn(l.f(vp[i])) >= 0 ) {
			vq.push_back(vp[i]);
			if ( sgn(l.f(vp[(i+1)%sz])) < 0 )
				vq.push_back(l.getItc(vp[i], vp[(i+1)%sz]));
		} else 
			if ( sgn(l.f(vp[(i+1)%sz])) >= 0 )
				vq.push_back(l.getItc(vp[i], vp[(i+1)%sz]));
	}
	vp = vq;
}
int n, h, f;
int l[kNMax], r[kNMax];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &h, &f);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%d%d", &l[i], &r[i]);
	double ans = 0;
	for ( int i = 0; i < n; i ++ ) {
		Point src(0, f), lp(l[i], h), rp(r[i], h);
		Point dl = lp - src, dr = rp - src;
		dl = dl * fabs((double)(f+h)/(f-h));
	   	dr = dr * fabs((double)(f+h)/(f-h));
		double len1 = r[i]-l[i], len2 = (src+dr).x-(src+dl).x;
		ans += (len1 + len2) * 2 * h;
	}
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < n; j ++ ) {
			poly.init();
			poly.cut(Line(Point(0, h), Point(-1, h)));
			poly.cut(Line(Point(0, -h), Point(1, -h)));
			poly.cut(Line(Point(0, f), Point(l[i], h)));
			poly.cut(Line(Point(r[i], h), Point(0, f)));
			poly.cut(Line(Point(0, -f), Point(r[j], -h)));
			poly.cut(Line(Point(l[j], -h), Point(0, -f)));
			double tmp = poly.calcArea();
			ans -= tmp;
		}
	printf("%.10lf\n", ans);
}
