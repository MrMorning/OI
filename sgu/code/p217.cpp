#include <cstdio>
#include <cmath>
#include <algorithm>
#define SIMPSON(a, b) (((b) - (a)) / 6 * (f(a) + 4 * f(((a) + (b)) / 2) + f(b)))
#define SQR(x) ((x) * (x))
using namespace std;
const double EPS = 10e-8;

double r1, r2;

inline double f(double z)
{
	return sqrt((SQR(r1) - SQR(z)) * (SQR(r2) - SQR(z)));
}

double calcArea(double l, double r)
{
	double mid = (l + r) / 2;
	double lval = SIMPSON(l, mid),
		   rval = SIMPSON(mid, r),
		   totVal = SIMPSON(l, r);
	if(fabs(lval + rval - totVal) < EPS)
		return totVal;
	return calcArea(l, mid) + calcArea(mid, r);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%lf%lf", &r1, &r2);
	if(r1 > r2)
		swap(r1, r2);
	printf("%.4lf\n", 8 * calcArea(0, r1));
}
