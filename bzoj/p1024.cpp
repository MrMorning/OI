#include <cstdio>
const double INFINITY = 10E100;
inline double min(double a, double b)
{return a < b ? a : b;}
inline double max(double a, double b)
{return a > b ? a : b;}
double cut(double x, double y, int k)
{
	if(k == 1)
		return max(x, y) / min(x, y);
	double tmp = x / k, res = INFINITY;
	for(int i = 1; i < k; i ++)
		res = min(res, max(cut(tmp * i, y, i), cut(x - tmp * i, y, k - i)));
	tmp = y / k;
	for(int i = 1; i < k; i ++)
		res = min(res, max(cut(x, i * tmp, i), cut(x, y - tmp * i, k - i)));
	return res;
}

int main()
{
	double x, y;
	int n;
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%d", &x, &y, &n);
	printf("%.6lf\n", cut(x, y, n));
}
