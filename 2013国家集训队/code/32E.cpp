#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const double kEps = 1e-8;

int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

bool lesser(double a, double b) {
	return sgn(a-b) < 0;
}

struct Point {
	double x, y;
	Point(){}
	Point(double xx, double yy):
		x(xx), y(yy){}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
} p0, p1, pw1, pw2, pm1, pm2;

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator* (const Point &p, double k) {
	return Point(p.x*k, p.y*k);
}

double dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

double calcDistToLine(Point p, double a, double b, double c) {
	return fabs(p.x*a+p.y*b+c)/sqrt(a*a+b*b);
}

bool isIntersected(Point p1, Point p2, Point q1, Point q2) {
	if ( lesser(max(p1.x, p2.x), min(q1.x, q2.x) )
			|| lesser(max(q1.x, q2.x), min(p1.x, p2.x))
			|| lesser(max(p1.y, p2.y), min(q1.y, q2.y))
			|| lesser(max(q1.y, q2.y), min(p1.y, p2.y)) )
		return false;
	if ( sgn(cross(q1-p1, p2-p1)) * sgn(cross(p2-p1, q2-p1)) >= 0
			&& sgn(cross(p1-q1, q2-q1)) * sgn(cross(q2-q1, p2-q1)) >= 0 )
		return true;
	return false;
}

Point getIntersection(Point p1, Point p2, Point q1, Point q2) {
	double a = p2.y - p1.y,
		   b = p1.x - p2.x,
		   c = -(a*p1.x + b*p1.y);
	Point v = q2 - q1;
	double d1 = calcDistToLine(q1, a, b, c),
		   d2 = calcDistToLine(q2, a, b, c);
	v = v * (d1/(d1+d2));
	return q1 + v;
}

Point getReflection(Point pt) {
	double a = pm2.y - pm1.y,
		   b = pm1.x - pm2.x,
		   c = -(a*pm1.x + b*pm1.y);
	double d = calcDistToLine(pt, a, b, c);
	Point norm(a, b);
	norm = norm * (2*d/sqrt(dot(norm, norm)));
	Point pr = norm + pt;
	if ( sgn(a*(pr.x+pt.x)/2+b*(pr.y+pt.y)/2+c) != 0 )
		pr = pt - norm;
	return pr;
}

bool crossWall(Point p1, Point p2) {
	return isIntersected(p1, p2, pw1, pw2);
}

bool crossMirror(Point p1, Point p2) {
	return !(sgn(cross(p1-p2, pm1-pm2)) == 0) && isIntersected(p1, p2, pm1, pm2);
}

void printYes() {
	puts("YES");
	exit(0);
}

void printNo() {
	puts("NO");
	exit(0);
}

int main() {
	freopen("t.in", "r", stdin);
	p0.read(); p1.read();
	pw1.read(); pw2.read();
	pm1.read(); pm2.read();

	if ( !crossWall(p0, p1) && !crossMirror(p0, p1) )
		printYes();
	if ( crossMirror(p0, p1) ) printNo();

	Point p2 = getReflection(p0);
	if ( !crossMirror(p1, p2) ) printNo();
	Point p3 = getIntersection(p1, p2, pm1, pm2);
	if ( !crossWall(p3, p0) && !crossWall(p3, p1) ) printYes();
	printNo();
}
