#include <cstdio>



int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d%d%d", &x[i], &p[i], &c[i]);
		sump[i] = sump[i - 1] + p[i];
		sum[i] = sum[i - 1] + p[i] * x[i];
	}
}
