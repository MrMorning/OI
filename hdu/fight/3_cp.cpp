#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef pair<double, double> pair_t;

const double FINAL_TEMP = 10e-4;
const double FREEZE = 0.98;
const int MALRCOF = 100;

struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
};

inline double rand_double(double x) {
	return x * ((double)rand() / RAND_MAX);
}

inline double sqr(double x) {
	return x * x;
}

double a, b, c, r, alpha, beta;
Point u;

pair_t calc1(double x0) {
	if ( x0 <= cos(alpha) * b )
		return make_pair(0, tan(alpha) * x0);
	else
		return make_pair(0, tan(beta) * (a - x0));
}

pair_t calc2(double x0) {
	if ( x0 < u.x - r || u.x + r < x0 )
		return make_pair(0, 0);
	double d = fabs(u.x - x0),
		   l = sqrt(sqr(r) - sqr(d));
	return make_pair(u.y - l, u.y + l);
}

double f(double x0) {
	pair_t pir1 = calc1(x0),
		   pir2 = calc2(x0);
	if ( pir1.first > pir2.second || pir1.second < pir2.first )
		return 0.0;
	if ( pir1.second < pir2.second )
		swap(pir1, pir2);
	if ( pir1.first < pir2.first )
		return pir2.second - pir2.first;
	return pir2.second - pir1.first;
}

double sim(double l, double r) {
	double m = (l + r) / 2;
	double val = (r - l) / 6 * (f(l) + 4 * f(m) + f(r));
	double lval = (m - l) / 6 * (f(l) + 4 * f((l + m) / 2) + f(m));
	double rval = (r - m) / 6 * (f(m) + 4 * f((m + r) / 2) + f(r));
	if ( fabs(val - (lval + rval)) < 10e-3 )
		return val;
	return sim(l, m) + sim(m, r);
}

double eval(const Point &p) {
	u = p;
	return sim(max(0.0, u.x - r), min(a, u.x + r));
}

int main() {
	freopen("t.in", "r", stdin);
	while ( 1 ) {
		scanf("%lf%lf%lf%lf", &a, &b, &c, &r);
		if ( a == 0 && b == 0 && c == 0 && r == 0 )
			break;
		if ( a < b )
			swap(a, b);
		if ( a < c )
			swap(a, c);
		alpha = acos((sqr(a) + sqr(b) - sqr(c)) / (2 * a * b));
		beta = acos((sqr(a) + sqr(c) - sqr(b)) / (2 * a * c));
		Point cur(0, 0);
		double cur_ener = eval(cur);
		for ( double cur_temp = a / 2; cur_temp > FINAL_TEMP; cur_temp *= FREEZE )
			for ( int rep = 0; rep < MALRCOF; rep ++ ) {
				Point next = cur;
				next.x += rand_double(cur_temp) * ((rand() % 2) ? -1 : 1);
				next.y += rand_double(cur_temp) * ((rand() % 2) ? -1 : 1);
				double next_ener = eval(next);
				if ( next_ener > cur_ener || exp((next_ener - cur_ener) / cur_temp) > rand_double(1.0) )
					cur = next, cur_ener = next_ener;
			}
		printf("%.2lf\n", eval(Point(0,0)));
		/*u = Point(2,1);
		for ( double st = 1; st <= 3; st += 0.1 ) {
		printf("%.2lf %.2lf\n", st, f(st));
		}*/
		printf("%.2lf\n", cur_ener);
	}
}
