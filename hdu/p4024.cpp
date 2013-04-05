#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;
#define SQR(x) ((x) * (x))
const double EPS = 10e-8;
double X1, Y1, X2, Y2, Lx, Ly, Vd, Vb, L;
double a, b, c;

double solveEq()
{
	double delta = SQR(b) - 4 * a * c;
	double r1 = (sqrt(delta) - b) / (2 * a),
		   r2 = (-sqrt(delta) - b) / (2 * a);
	if(r1 < 0)
		r1 = 10e100;
	if(r2 < 0)
		r2 = 10e100;
	double res = min(r1, r2);
	if(res < L / Vb)
		return 10e100;
	return res;
}

double solve1()
{
	a = SQR(Vd) - SQR(Lx) - SQR(Ly);
	b = -2 * X1 * Lx - 2 * Y1 * Ly - 2 * Vd * (1 + Vd / Vb) * L;
	c = SQR(L * (1 + Vd / Vb)) - SQR(X1) - SQR(Y1);
	return solveEq();
}

double solve2()
{
	a = SQR(Vd) - SQR(Lx) - SQR(Ly);
	b = -2 * X1 * Lx - 2 * Y1 * Ly + 2 * Vd * (1 - Vd / Vb) * L;
	c = SQR(L * (1 - Vd / Vb)) - SQR(X1) - SQR(Y1);
	return solveEq();
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2, &Lx, &Ly, &Vd, &Vb, &L);
		if(fabs(X1) < EPS && fabs(Y1) < EPS && fabs(X2) < EPS)
			if(fabs(Y2) < EPS && fabs(Lx) < EPS && fabs(Ly) < EPS && fabs(L) < EPS)
				break;
		X1 -= X2, Y1 -= Y2;
		printf("%.3lf %.3lf\n", L, min(solve1(), solve2()));
	}
}
