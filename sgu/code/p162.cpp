#include <cstdio>
#include <cmath>
#define SQR(x) ((x) * (x))
int main()
{
	double a, b, c, a1, b1, c1;
	scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &c1, &b1, &a1);
	double m = SQR(b) + SQR(c) - SQR(a1),
		   n = SQR(a) + SQR(c) - SQR(b1),
		   p = SQR(a) + SQR(b) - SQR(c1);
	printf("%.4lf\n", sqrt(SQR(a * b * c) - (SQR(a * m) + SQR(b * n) + SQR(c * p)) / 4 + m * n * p / 4) / 6);
}

