#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
ll n, x1, y1, x2, y2, xi, yi, xc, yc;
void noSol()
{
	printf("no solution\n");
	exit(0);
}

void output()
{
	printf(LL_FMT" "LL_FMT"\n", xi == -1 ? xc - 1 : xc, yi == -1 ? yc - 1 : yc);
	exit(0);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf(LL_FMT LL_FMT LL_FMT LL_FMT LL_FMT, &x1, &y1, &x2, &y2, &n);
	if(x1 == x2 || y1 == y2)
		noSol();
	xi = (x2 - x1) / abs(x2 - x1), yi = (y2 - y1) / abs(y2 - y1);
	xc = x1, yc = y1;
	for(int cnt = 1; ; cnt ++)
	{
		if(xc == x2 && yc == y2)
			noSol();
		if(cnt == n)
			output();
		ll cross1 = ((xc + xi - x1) * (y2 - y1) - (yc + yi - y1) * (x2 - x1))
			* ((xc + xi - x1) * (y2 - y1) - (yc - y1) * (x2 - x1));
		ll cross2 = ((xc + xi - x1) * (y2 - y1) - (yc + yi - y1) * (x2 - x1))
			* ((xc - x1) * (y2 - y1) - (yc + yi - y1) * (x2 - x1));
		if(cross1 <= 0)
			xc += xi;
		if(cross2 <= 0)
			yc += yi;
	}
}
