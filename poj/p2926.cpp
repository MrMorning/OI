#include <cstdio>
#include <algorithm>
const double INFINITY = 10E100;
int n;
double max_val[32], min_val[32], x[5];
int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 0; i < 32; i ++)
		max_val[i] = -INFINITY, min_val[i] = INFINITY;
	scanf("%d", &n);
	while(n --)
	{
		for(int i = 0; i < 5; i ++)
			scanf("%lf", &x[i]);
		for(int s = 0; s < 32; s ++)
		{
			double res = 0;
			for(int j = 0; j < 5; j ++)
				if(s & (1 << j))
					res += x[j];
				else
					res -= x[j];
			max_val[s] = std::max(max_val[s], res);
			min_val[s] = std::min(min_val[s], res);
		}
	}
	double ans = 0;
	for(int i = 0; i < 32; i ++)
		ans = std::max(ans, max_val[i] - min_val[i]);
	printf("%.2lf\n", ans);
}
