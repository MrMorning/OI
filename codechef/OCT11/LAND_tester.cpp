#include <cstdio>
#include <cmath>
int a[4];
int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 0; i < 4; i ++)
		scanf("%d", &a[i]);
	for(int k = 1; k <= 50; k ++)
	{
		double res = 0;
		for(int i = 0; i < 4; i ++)
			res += pow(2, fabs(k - a[i]));
		printf("k = %d, diff = %.3lf\n", k, res);
	}
}
