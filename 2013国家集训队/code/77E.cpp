#include <cstdio>
#include <cmath>
struct Point {
	double x, y;
	Point(double xx, double yy):x(xx),y(yy){}
};
double sqr(double x){return x*x;}
double getDist(Point p1, Point p2) {
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
double calcRad(Point p1, Point p2, Point p3) {
	double a = getDist(p1, p2), 
		   b = getDist(p2, p3),
		   c = getDist(p3, p1),
		   p = (a+b+c)/2,
		   s = sqrt(p*(p-a)*(p-b)*(p-c));
	return a*b*c/(4*s);
}
Point f(double x, double y) {
	double p = sqrt(x*x+y*y), 
		   cost = x/p,
		   sint = y/p;
	p = 1/p;
	return Point(cost*p, sint*p);
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		double R, r, k;
		scanf("%lf%lf%lf", &R, &r, &k);
		double x = (R+r)/(4*R*r),
			   y = k*(R-r)/(2*R*r),
			   r2 = (R-r)/(4*R*r);
		printf("%.10lf\n", calcRad(f(x,y-r2), f(x+r2,y), f(x-r2, y)));
	}
}
