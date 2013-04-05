#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
double a, b, l;
double sqr(double x) { return x*x; }

double eval(double s) {
	double r = sqrt(sqr(l)-sqr(s));
	return (r*a+s*b-r*s)/l;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%lf", &a, &b, &l);
	if ( a > b ) swap(a, b);
	if ( l <= a ) printf("%.10lf\n", l);
	else if ( l <= b ) printf("%.10lf\n", a);
	else {
		double lb = 0, rb = l;
		for ( ; rb-lb > 1e-8; ) {
			double lmid = lb+(rb-lb)/3,
				   rmid = rb-(rb-lb)/3;
			if ( eval(lmid) > eval(rmid) )
				lb = lmid;
			else
				rb = rmid;
		}
		if ( eval(lb) > 0 )
			printf("%.10lf\n", eval(lb));
		else puts("My poor head =(");
	}
}
