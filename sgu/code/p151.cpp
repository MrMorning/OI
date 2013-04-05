#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#define EPS 10e-8
#define SQR(x) ((x) * (x))
#define ADJUST(x) (fabs(x) < EPS ? 0 : (x))
double c, b, m;
void noSol()
{
	printf("Mission impossible\n");
	exit(0);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%lf", &c, &b, &m);
	if(2 * m > b + c || 2 * m < fabs(b - c))
		noSol();
	else
	{
		double xc = (4 * SQR(m) - SQR(b) - SQR(c)) / (2 * c);
		double yc = sqrt(ADJUST(SQR(b) - SQR(xc)));
		printf("%.5lf %.5lf\n", .0, .0);
		printf("%.5lf %.5lf\n", ADJUST(c), .0);
		printf("%.5lf %.5lf\n", ADJUST(xc), ADJUST(yc));
	}
}
