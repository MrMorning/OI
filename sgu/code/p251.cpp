#include <cstdio>
int n, r[5];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	if(n >= 5)
	{
		printf("NO\n");
		return 0;
	}
	for(int i = 1; i <= n; i ++)
		scanf("%d", &r[i]);
	if(n == 3)
	{
		printf("YES\n");
		printf("%.4lf %.4lf\n", 0.0, (double)r[1] + r[2] + r[3]);
		printf("%.4lf %.4lf\n", 1.0, 0.0);
		printf("%.4lf %.4lf\n", -1.0, 0.0);
	}
	else
	{
		if(r[1] == r[2])
		{
			int h = r[1] + r[3] + r[4];
			printf("YES\n");
			printf("%.4lf %.4lf\n", (double)(r[1] + r[2] + r[3]) / h, (double)h);
			printf("%.4lf %.4lf\n", -(double)(r[1] + r[2] + r[3]) / h, (double)h);
			printf("%.4lf %.4lf\n", 1.0, 0.0);
			printf("%.4lf %.4lf\n", -1.0, 0.0);
		}
		else if(r[1] + r[3] + r[4] + r[2] + r[3] + r[4] == 2 * r[1] + 2 * r[2] + 2 * r[3])
		{
			printf("YES\n");
			printf("%.4lf %.4lf\n", 0.0, (double)r[1] + r[3] + r[4]);
			printf("%.4lf %.4lf\n", 0.0, -(double)(r[2] + r[3] + r[4]));
			printf("%.4lf %.4lf\n", 1.0, 0.0);
			printf("%.4lf %.4lf\n", -1.0, 0.0);
		}
		else
			printf("NO\n");
	}
}
