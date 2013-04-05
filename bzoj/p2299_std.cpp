#include <cstdio>
#include <cstdlib>

int gcd(int a, int b)
{
	int t;
	while (b)
	{
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

void solve(int a, int b, int c, int& x, int& y)
{
	if (b == 0)
	{
		x = c / a;
		y = 0;
		return;
	}
	solve(b, a % b, c, y, x);
	y -= a / b * x;
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	for (scanf("%d", &_); _--; )
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		/*
		   a = abs(a);
		   b = abs(b);
		   c = abs(c);
		   d = abs(d);
		   */
		int g = gcd(a, b);
		if (c % g == 0 && d % g == 0)
		{
			a /= g;
			b /= g;
			c /= g;
			d /= g;
			bool canl[2][2] = {0}, canr[2][2] = {0};
			int xl, yl, xr, yr;
			solve(a, b, c, xl, yl);
			solve(b, a, d, xr, yr);
#if DB & 1
			fprintf(stderr, "%d %d\n", xl, yl);
			fprintf(stderr, "%d %d\n", xr, yr);
#endif
			xl &= 1, yl &= 1, xr &= 1, yr &= 1;
			canl[xl][yl] = true;
			canl[(xl ^ b) & 1][(yl ^ a) & 1] = true;
			canr[xr][yr] = true;
			canr[(xr ^ a) & 1][(yr ^ b) & 1] = true;
			if ((canl[0][0] && canr[0][0]) || (canl[0][1] && canr[0][1])
					|| (canl[1][0] && canr[1][0]) || (canl[1][1] && canr[1][1]))
				puts("Y");
			else
				puts("N");
		}
		else
			puts("N");
	}
}
