#include <cstdio>
#include <cmath>
#include <cassert>
const double EPS = 10e-8;
struct Point
{
	double x, y;
};
void solveEq(double a, double b, double c, double &x1, double &x2)
{
	double delta = b * b - 4 * a * c;
	assert(delta >= 0);
	double tmp = sqrt(delta);
	x1 = (tmp - b) / (2 * a);
	x2 = (-tmp - b) / (2 * a);
}

double dx, dy, r, xA, yA, xB, yB;

void getIntersect(double A, double B, double C, Point &p1, Point &p2)
{
	Point p[2];
	if(fabs(B) < EPS)
	{
		double k = -C / A;
		double y1, y2;
		solveEq(1, 0, k * k - r * r, y1, y2);
		p[0].x = p[1].x = k;
		p[0].y = y1, p[1].y = y2;
	}
	else
	{
		double k = -A / B, b = -C / B;
		double x1, x2;
		solveEq(1 + k * k, 2 * b * k, b * b - r * r, x1, x2);
		p[0].x = x1, p[1].x = x2;
		p[0].y = k * x1 + b, p[1].y = k * x2 + b;
	}
	p1 = p[0], p2 = p[1];
}

double calcCosAgl(const Point &p)
{
	double d1 = (p.x - xA) * (p.x - xA) + (p.y - yA) * (p.y - yA);
	double d2 = (p.x - xB) * (p.x - xB) + (p.y - yB) * (p.y - yB);
	double tmp = (xA - p.x) * (xB - p.x) + (yA - p.y) * (yB - p.y);
	return tmp / (sqrt(d1) * sqrt(d2));
}

void calcCore(Point &p1, Point &p2)
{
	double xM = (xA + xB) / 2, yM = (yA + yB) / 2;
	double A = xA - xB, B = yA - yB;
	double C = -(A * xM + B * yM);

	double m = -2 * xA, n = -2 * yA, T = xA * xA + yA * yA - r * r, s = 2 * r;
	double p = m * m - s * s, q = n * n - s * s, l = 2 * m * T, v = 2 * n * T, u = 2 * m * n;
	if(fabs(B) > EPS)
	{
		double k = -A / B, b = -C / B;
		double x1, x2;
		solveEq(p + q * k * k + u * k, 2 * q * k * b + l + v * k + u * b, q * b * b + v * b + T * T, x1, x2);
		p1.x = x1, p2.x = x2;
		p1.y = k * x1 + b, p2.y = k * x2 + b;
	}
	else
	{
		double x1 = -C / A, x2 = -C / A;
		double y1, y2;
		solveEq(q, v + u * x1, p * x1 * x1 + l * x1 + T * T, y1, y2);
		p1.x = x1, p1.y = y1;
		p2.x = x2, p2.y = y2;
	}
}
Point core[2], pnt[4];
void solve()
{
	scanf("%lf%lf%lf%lf%lf%lf%lf", &dx, &dy, &r, &xA, &yA, &xB, &yB);
	xA -= dx, xB -= dx;
	yA -= dy, yB -= dy;
	calcCore(core[0], core[1]);
	for(int t = 0; t < 2; t ++)
		getIntersect(core[t].y, -core[t].x, 0, pnt[t * 2], pnt[t * 2 + 1]);
	double bigAgl = 10e100;
	int res;
	for(int t = 0; t < 4; t ++)
	{
		double agl = calcCosAgl(pnt[t]);
		if(agl < bigAgl)
			bigAgl = agl, res = t;
	}
	printf("%.6lf %.6lf\n", pnt[res].x + dx , pnt[res].y + dy);
}

int main()
{
	freopen("t.in", "r", stdin);
	int __;
	scanf("%d", &__);
	while(__ --)
		solve();
}
