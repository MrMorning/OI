#include <cstdio>
#include <cmath>
#include <cstdlib>
#define SQR(x) ((x) * (x))
#define EQUAL(x, y) (fabs((x) - (y)) < 10e-8)
double AH, AD, AM;
void noSol()
{
	printf("NO\n");
	exit(0);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%lf", &AH, &AD, &AM);
	if(! (AH <= AD && AD <= AM))
		noSol();
	if(EQUAL(AH, AD) && !EQUAL(AH, AM))
		noSol();
	if(EQUAL(AH, AM) && !EQUAL(AH, AD))
		noSol();
	if(EQUAL(AD, AM) && !EQUAL(AD, AH))
		noSol();
	double l;
	double s = sqrt(SQR(AM) - SQR(AH));
	double x = s - sqrt(SQR(AD) - SQR(AH));
	if(EQUAL(AD, AM) && EQUAL(AM, AH))
		l = 1;
	else
	{
		double tmp = (s * x * (x - s) - SQR(AH) * x) / (x - s);
		if(tmp < 0)
			noSol();
		l = sqrt(tmp);
	}
	printf("YES\n");
	printf("%.8lf %.8lf\n", 0.0, AH); 
	printf("%.8lf %.8lf\n", -(s + l), 0.0);
	printf("%.8lf %.8lf\n", l - s, 0.0);
}
