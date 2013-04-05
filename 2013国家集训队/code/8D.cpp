#include <cstdio>
#include <cmath>
#include <vector>
#define foreach(I, C) for ( __typeof((C).begin()) I = (C).begin(); I != (C).end(); I++ )
using namespace std;

const double PI = acos(-1);
const double kEps = 1e-10;

inline double sqr(double x) { return x * x; }
inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

struct Point {
	double x, y;
	Point(){}
	Point(double xx, double yy): x(xx), y(yy){}
	void read() {
		int a, b;
		scanf("%d%d", &a, &b);
		x = a, y = b;
	}
} cine, home, shop;
double t1, t2;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}
Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator* (const Point &p1, double k) {
	return Point(p1.x * k, p1.y * k);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double getDist(const Point &p1, const Point &p2) {
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}

void rotate(Point &p, double agl) {
	Point vx(cos(-agl), sin(-agl)),
		  vy(cos(PI/2-agl), sin(PI/2-agl));
	p = Point(dot(vx, p), dot(vy, p));
}

vector<Point> getCross(Point c1, double r1, Point c2, double r2) {
	vector<Point> res;
	double d = getDist(c1, c2);
	if ( sgn(r1 + r2 - d) < 0 || sgn(fabs(r1 - r2) - d) > 0 ) return res;
	if ( sgn(r1 + r2 - d) == 0 ) {
		Point vt = c2 - c1;
		vt = vt * (1/d) * r1;
		res.push_back(c1 + vt);
		return res;
	}
	double agl = acos((sqr(r1) + sqr(d) - sqr(r2)) / (2 * r1 * d));
	Point vm = c2 - c1;
	vm = vm * (1/d) * r1;
	rotate(vm, agl);
	res.push_back(c1 + vm);
	vm = c2 - c1;
	vm = vm * (1/d) * r1;
	rotate(vm, -agl);
	res.push_back(c1 + vm);
	return res;
}

bool contain(Point c, double r, Point p) {
	return sgn(getDist(c, p) - r) <= 0;
}

bool test(Point c1, double r1, Point c2, double r2, Point c3, double r3, Point p) {
	return contain(c1, r1, p) && contain(c2, r2, p) && contain(c3, r3, p);
}

bool check(double x) {
	Point c1 = cine, c2 = home, c3 = shop;
	double r1 = x, r2 = max(0.0, t2 - x), r3 = max(0.0, t1 - x - getDist(shop, home));
	if ( test(c1, r1, c2, r2, c3, r3, c1) ) return true;
	if ( test(c1, r1, c2, r2, c3, r3, c2) ) return true;
	if ( test(c1, r1, c2, r2, c3, r3, c3) ) return true;
	vector<Point> vp = getCross(c1, r1, c2, r2);
	foreach(it, vp)
		if ( test(c1, r1, c2, r2, c3, r3, *it) ) return true;
	vp = getCross(c1, r1, c3, r3);
	foreach(it, vp)
		if ( test(c1, r1, c2, r2, c3, r3, *it) ) return true;
	vp = getCross(c2, r2, c3, r3);
	foreach(it, vp)
		if ( test(c1, r1, c2, r2, c3, r3, *it) ) return true;
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	int tt1, tt2;
	scanf("%d%d", &tt1, &tt2);
	cine.read(); home.read(); shop.read();

	t1 = tt1 + getDist(cine, shop) + getDist(shop, home);
	t2 = tt2 + getDist(cine, home);

	double lb = 0, rb = min(t1 - getDist(shop, home), t2);
	for ( double mid = (lb + rb) / 2, cnt = 0; cnt < 100; mid = (lb + rb) / 2, cnt += 1 ) {
		if ( check(mid) ) lb = mid;
		else rb = mid;
	}
	double ans = lb;
	if ( sgn(getDist(cine, shop) + getDist(shop, home) - t2) <= 0 )
		ans = max(ans, min(t1, t2));
	printf("%.8lf\n", ans);
}
