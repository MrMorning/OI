#include <cstdio>
#include <cmath>
const double EPS = 10e-4;
int n;
double a[4];
double calc(double val)
{
	double res = 0;
	for(int i = 0; i < n; i ++)
		res += pow(2, fabs(a[i] - val));
	return res;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%lf", &a[i]);
	double lb = 1, rb = 50;
	for(; rb - lb > EPS; )
	{
		double lmid = lb + (rb - lb) / 3,
			   rmid = lb + (rb - lb) / 3 * 2;
		if(calc(lmid) < calc(rmid))
			rb = rmid;
		else
			lb = lmid;
	}
	for(int k = 1; k <= 50; k ++)
		printf("%d %lf\n", k, calc(k));
	printf("%.3lf\n", rb);
}
