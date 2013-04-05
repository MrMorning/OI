#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#define EPS 10e-8
#define SQR(x) ((x) * (x))
#define ADJUST(x) (fabs(x) < EPS ? 0 : (x))
#define EQUAL(a, b) fabs((a) - (b)) < EPS
double a, b, m;
void noSol()
{
	printf("Mission impossible\n");
	exit(0);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%lf", &a, &b, &m);
	double tmp = (SQR(a) + SQR(b) - 2 * SQR(m)) / 2; 
	if(ADJUST(tmp) < 0)
		noSol();
	double c = 2 * sqrt(tmp);
	if(a + b <= c || b + c <= a || a + c <= b)
		noSol();
	double p = (a + b + c) / 2;
	double area = sqrt(p * (p - a) * (p - b) * (p - c));
	double h = 2 * area / c, l = sqrt(SQR(a) - SQR(h));
	if(SQR(a) + SQR(c) - SQR(b) < 0)
		l *= -1;
	printf("%.5lf %.5lf\n", ADJUST(l), ADJUST(h));
	printf("%.5lf %.5lf\n", .0, .0);
	printf("%.5lf %.5lf\n", ADJUST(c), .0);

	assert(EQUAL(sqrt(SQR(l) + SQR(h)), a));
	assert(EQUAL(sqrt(SQR(l - c) + SQR(h)), b));
	assert(EQUAL(sqrt(SQR(l - c / 2) + SQR(h)), m));
	assert(fabs(l) <= 10000);
	assert(fabs(h) <= 10000);
	assert(fabs(c) <= 10000);
}
