#include <cstdio>
#include <cmath>
int na, nb, nc;
int a[6000], b[6000], c[6000];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &na);
	for(int i = 0; i < na; i ++)
	{
		double x;
		scanf("%lf", &x);
		a[i] = (int)round(x * 1000000) - 2000000;
		if(a[i] <= 0)
			b[nb ++] = i;
		else
			c[nc ++] = i;
	}
	printf("yes\n");
	long long s = 0;
	nb = 0, nc = 0;
	for(int i = 0; i < na; i ++)
		if(s < 0)
			printf("%d ", c[nc] + 1), s += a[c[nc ++]];
		else
			printf("%d ", b[nb] + 1), s += a[b[nb ++]];
}
