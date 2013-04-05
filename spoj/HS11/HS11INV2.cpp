#include <cstdio>
#include <cmath>
double a[11];
int n;

double calc(double r)
{
	double res = 0;
	for(int i = 0; i <= n; i ++)
		res += a[i] / pow(1 + r, i);
	return res;
}

double adjust(double x)
{
	if(fabs(x) < 10e-6)
		return fabs(x);
	else
		return x;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	double cnt = 0;
	for(int i = 0; i < n; i ++)
	{
		scanf("%lf", &a[i]);
		cnt += a[i];
	}
	scanf("%lf", &a[n]);
	a[n] *= -1;
	double lb = -1, rb = 1;
	for(double mid = (lb + rb) / 2; rb - lb > 10e-8; mid = (lb + rb) / 2)
		if(calc(mid) < 0)
			lb = mid;
		else
			rb = mid;
	printf("%.2lf\n", adjust(rb * 100));
}
