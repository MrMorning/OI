#include <cstdio>
#include <cstdlib>
#include <cmath>
#define EPS 1e-12
#define sqr(x) ((x) * (x))

using namespace std ;

template <typename T> T max(T a, T b)
{
	if(a < b)
		return b;
	return a;
}

template <typename T> T min(T a, T b)
{
	if(a < b)
		return a;
	return b;
}

double b1, t1, b2, t2, len, d1, d2, g;

double calc(double x0, double x1, double x, double y)
{
	double a = y / (sqr(x) - x1 * x - x0 * x + x0 * x1);
	double m = (x1 - x0) / 2.0;
	double h = a * (m - x0) * (m - x1);
	double cost = 2.0 * h ;
	double v1= g * cost;
	double v2= sqr(x1 - x0) / cost * g / 4.0;  
	return v1 + v2;
}

double calc(double s, double t, double mid, double down, double up)
{
	double res= min(calc(s, t, mid, down), calc(s, t, mid, up));
	double a = (-1.0) / (s + t);
	double y= a * (mid - s) * (mid - t);
	if(y > down && y < up)
		res= min(res, calc(s, t, mid, y));
	return res;
}

double calc(double pos)
{
	return max(calc(0, d1 + pos, d1, b1, t1), calc(0, len - pos + d2, len - pos, b2, t2));
}

void init()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &b1, &t1, &b2, &t2, &len, &d1, &d2, &g) != -1)
	{
		double l= 0, r= len, mid1, mid2;
		while(l + EPS < r)
		{
			mid1= l + (r - l) / 3.0;
			mid2= l + (r - l) / 3.0 * 2.0; 
			double v1= calc(mid1), v2= calc(mid2);
			if(v1 < v2)
				r= mid2;
			else
				l= mid1;
		}
		printf("%.4lf\n", sqrt(calc);
				}
				}

				int main()
				{
				init();
				return 0 ;
				}
