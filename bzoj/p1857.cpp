#include <cstdio>
#include <cmath>
const double EPS = 10E-6;
double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, P, Q, R;
inline double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double calc2(double lTmp, double rTmp)
{
	double Ex = Ax + lTmp * (Bx - Ax), Ey = Ay + lTmp * (By - Ay);
	double Fx = Cx + rTmp * (Dx - Cx), Fy = Cy + rTmp * (Dy - Cy);
	return dist(Ax, Ay, Ex, Ey) / P + dist(Ex, Ey, Fx, Fy) / R + dist(Fx, Fy, Dx, Dy) / Q;
}
double calc1(double lTmp)
{
	double l = 0, r = 1, mid = (l + r) / 2;
	while(r - l > EPS)
	{
		if(calc2(lTmp, mid) > calc2(lTmp, mid + EPS))
			l = mid;
		else
			r = mid;
		mid = (l + r) / 2;
	}
	return calc2(lTmp, mid);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%lf%lf", &Ax, &Ay, &Bx, &By);
	scanf("%lf%lf%lf%lf", &Cx, &Cy, &Dx, &Dy);
	scanf("%lf%lf%lf", &P, &Q, &R);
	double l = 0, r = 1, mid = (l + r) / 2;
	while(r - l > EPS)
	{
		if(calc1(mid) > calc1(mid + EPS))
			l = mid;
		else
			r = mid;
		mid = (l + r) / 2;
	}
	printf("%.2lf\n", calc1(mid));

}
