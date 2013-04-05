#include <ctime>
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
double cos_alpha, tan_alpha, tan_beta;
Point u;

pair_t calc1(double x0) {
	if ( x0 <= cos_alpha * b )
		return make_pair(0, tan_alpha * x0);
	else
		return make_pair(0, tan_beta * (a - x0));
}

pair_t calc2(double x0) {
	if ( x0 < u.x - r || u.x + r < x0 )
		return make_pair(0, 0);
	double d = fabs(u.x - x0),
		   l = sqrt(sqr(r) - sqr(d));
	return make_pair(u.y - l, u.y + l);
}

double calc_f(double x0) {
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


double sim(double l, double r, double lval, double mval, double rval)
{
	double now = (r - l) * (lval + 4 * mval + rval) / 6, mid = (l + r) / 2;
	double tmp1 = calc_f((l + mid) / 2), tmp2 = calc_f((mid + r) / 2);
	if(fabs(now - (mid - l) * (lval + 4 * tmp1 + mval) / 6 
				- (r - mid) * (mval + 4 * tmp2 + rval) / 6) < 10e-4)
		return now;
	else
		return sim(l, mid, lval, tmp1, mval) + sim(mid, r, mval, tmp2, rval);
}

double eval(const Point &p) {
	u = p;
	double lb = max(0.0, u.x - r),
		   rb = min(a, u.x + r);
	return sim(lb, rb, calc_f(lb), calc_f((lb + rb) / 2), calc_f(rb));
}
int main() {
	srand(time(NULL));
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
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
		cos_alpha = cos(alpha);
		tan_alpha = tan(alpha);
		tan_beta = tan(beta);
		Point cur(0, 0);
		double x1 = cos(alpha) * b,
			   y1 = sin(alpha) * b,
			   x2 = a, y2 = 0,
			   x3 = 0, y3 = 0;
		cur.x = (a * x1 + b * x2 + c * x3) / (a + b + c);
		cur.y = (a * y1 + b * y2 + c * y3) / (a + b + c);
		double cur_ener = eval(cur);
		double tmp = eval(Point((x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3));
		if ( tmp > cur_ener ) {
			cur.x = (x1 + x2 + x3) / 3, cur.y = (y1 + y2 + y3) / 3;
			cur_ener = tmp;
		}
		for ( double cur_temp = a; cur_temp > FINAL_TEMP; cur_temp *= FREEZE )
			for ( int rep = 0; rep < MALRCOF; rep ++ ) {
				Point next = cur;
				next.x += rand_double(cur_temp) * ((rand() % 2) ? -1 : 1);
				next.y += rand_double(cur_temp) * ((rand() % 2) ? -1 : 1);
				double next_ener = eval(next);
				if ( fabs(next_ener) > 10e-6 && (next_ener > cur_ener || exp((next_ener - cur_ener) / cur_temp) > rand_double(1.0)) )
					cur = next, cur_ener = next_ener;
			}
		printf("%.2lf\n", cur_ener);
	}
}
