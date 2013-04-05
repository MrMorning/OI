#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m, y, x[1000];
double f[1001][10001];
int g[1001][10001];
const double oo = 10e100;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &y);
	for(int i = 0; i < n; i ++)
		scanf("%d", &x[i]); 
	for(int j = 0; j <= m; j ++)
		f[0][j] = oo;
	f[0][0] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= m; j ++)
		{
			f[i][j] = oo;
			for(int k = 0; k <= j; k ++)
			{
				double val = f[i - 1][j - k] + fabs((double)x[i - 1] / y - (double)k / m);
				if(val < f[i][j])
				{
					f[i][j] = val;
					g[i][j] = k;
				}
			}
		}
	printf("%.3lf\n", f[n][m]);
}
