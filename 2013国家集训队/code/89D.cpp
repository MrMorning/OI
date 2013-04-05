#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double kInf = 1e100;
const double kEps = 1e-8;
int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}
double sqr(double x) { return x * x; }
struct Point {
	double x, y, z;
	void scan() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
} A, O, v;
double R;
int n;
double eval(Point T, double r) {
	double a = sqr(v.x)+sqr(v.y)+sqr(v.z),
		   b = 2*((A.x-T.x)*v.x+(A.y-T.y)*v.y+(A.z-T.z)*v.z),
		   c = sqr(A.x-T.x)+sqr(A.y-T.y)+sqr(A.z-T.z)-sqr(r);
	double t = sqr(b)-4*a*c;
	if ( sgn(t) < 0 ) return kInf; 
	t = sqrt(t);
	double res1 = (t-b)/(2*a),
		   res2 = (-t-b)/(2*a);
	if ( sgn(res1) < 0 && sgn(res2) < 0 ) return kInf;
	else if ( sgn(res1) >= 0 && sgn(res2) < 0 ) return res1;
	else if ( sgn(res1) < 0 && sgn(res2) >= 0 ) return res2;
	else return min(res1, res2);
}

int main() {
	freopen("t.in", "r", stdin);
	A.scan(); v.scan();
	scanf("%lf", &R);
	scanf("%d", &n);
	double ans = kInf;
	for ( int i = 1; i <= n; i ++ ) {
		O.scan();
		int m;
		double r;
		scanf("%lf%d", &r, &m);
		ans = min(ans, eval(O, r + R));
		while ( m -- ) {
			Point p;
			p.scan();
			p.x += O.x; p.y += O.y; p.z += O.z;
			ans = min(ans, eval(p, R));
		}
	}
	if ( ans == kInf )
	   puts("-1");
	else
		printf("%.10lf\n", ans);
}
