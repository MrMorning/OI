#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cmath>

const int kTst = 2000000;
const double PI = acos(-1);
const double kEps = 1e-8;

double randDouble(double l, double r) {
	return (double)rand()/RAND_MAX*(r-l)+l;
}

inline double sqr(double x) { return x * x; }

struct Point {
	double x, y, z;
	Point(double xx, double yy, double zz):
		x(xx), y(yy), z(zz){}
	Point(){}
} p1, p2;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

bool check(Point q, Point p) {
	double a = dot(q,q), 
		   b = dot(p,p),
		   c = dot(p-q,p-q);
	return a+c < b;
}

double r;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%lf", &r);
	scanf("%lf%lf%lf", &p1.x, &p1.y, &p1.z);
	scanf("%lf%lf%lf", &p2.x, &p2.y, &p2.z);

	int cnt = 0;
	for ( int tst = 0; tst < kTst; tst ++ ) {
		Point q;
		q.x = randDouble(-r,r);
		double r2 = sqrt(sqr(r)-sqr(q.x)),
			   agl = randDouble(0,2*PI);
		q.y = r2*cos(agl), q.z = r2*sin(agl);

		cnt += check(q,p1) || check(q, p2);
	}
	printf("%.3lf\n", (double)cnt / kTst * 4 * PI * sqr(r));
}
