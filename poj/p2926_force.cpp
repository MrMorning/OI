#include <cstdio>
#include <cmath>
const int N_MAX = 100000;
double val[N_MAX][5], ans = -10E100;
int n;
double dist(int i, int j)
{
	double ret = 0;
	for(int k = 0; k < 5; k ++)
		ret += fabs(val[i][k] - val[j][k]);
	return ret;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < 5; j ++)
			scanf("%lf", &val[i][j]);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(dist(i, j) > ans)
				ans = dist(i, j);
	printf("%.2lf\n", ans);
}
