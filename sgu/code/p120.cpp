#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cassert>
#define SQR(x) ((x) * (x))
using namespace std;
const double EPS = 10e-8;
const double PI = 4 * atan(1);
struct Point
{
	double x, y;
} ans[150];
int n, p1, p2;

void getVerLine(double x1, double y1, double x2, double y2, double &av, double &bv, double &cv)
{
	double a = y2 - y1,
		   b = x1 - x2;
	av = -b, bv = a;
	cv = -(av * (x1 + x2) / 2 + bv * (y1 + y2) / 2);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &p1, &p2);
	p1 --, p2 --;
	double x1, y1, x2, y2;
	scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	if((p2 - p1 + n) % n > n / 2)
		swap(p1, p2), swap(x1, x2), swap(y1, y2);
	double av, bv, cv;
	getVerLine(x1, y1, x2, y2, av, bv, cv);
	double alpha = (double)((p2 - p1 + n) % n) / n * 2 * PI,
		   d = sqrt(SQR(x1 - x2) + SQR(y1 - y2)),
		   r = d / 2 / sin(alpha / 2);
	double xc, yc;
	if(fabs(bv) < EPS)
	{
		assert(fabs(x1 - x2) > EPS);
		xc = -cv / av;
		yc = (sin(alpha) * SQR(r)
			-x2 * y1 + y2 * x1) / (-x2 + x1);
	}
	else
	{
		double u = -x2 * y1 + y2 * x1 + cv / bv * (-x2 + x1) + sin(alpha) * SQR(r),
			   v = -av / bv * (-x2 + x1) - y1 + y2;
		xc = u / v;
		yc = (-av * xc - cv) / bv;
	}
	x1 -= xc, y1 -= yc, x2 -= xc, y2 -= yc;
	ans[p1].x = x1, ans[p1].y = y1;
	double beta = 2 * PI / n;
	for(int i = (p1 + 1) % n; i != p1; i = (i + 1) % n)
	{
		double xj = ans[(i - 1 + n) % n].x,
			   yj = ans[(i - 1 + n) % n].y,
			   &xi = ans[i].x, &yi = ans[i].y;
		double u = SQR(r) * sin(beta),
			   v = SQR(r) * cos(beta);
		if(fabs(yj) < EPS)
			yi = u / -xj, xi = (v - yi * yj) / xj;
		else
			yi = (v - u * xj / yj) / (SQR(xj) / yj + yj), xi = (yi * xj + u) / yj;
	}
	
	for(int i = 0; i < n; i ++)
#define SET(x) (fabs(x) < EPS ? 0 : (x))
		printf("%.6lf %.6lf\n", SET(ans[i].x + xc), SET(ans[i].y + yc));
}
