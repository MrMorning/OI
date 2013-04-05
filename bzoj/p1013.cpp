#include <cstdio>
#define SQR(x) ((x)*(x))
#define MAXN 11
#define EPS 1E-8
int n;
double a[MAXN][MAXN], matrix[MAXN][MAXN];

inline double abs(double x)
{
	return x > 0 ? x : -x;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n + 1; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%lf", &a[i][j]);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
		{
			matrix[i][j] = 2 * (a[i + 1][j] - a[i][j]);
			matrix[i][n + 1] += SQR(a[i + 1][j]) - SQR(a[i][j]);
		}
	int j = 1;
	for(int i = 1; i <= n; i ++)
	{
		int p = i;
		while(j <= n + 1 && abs(matrix[p][j]) < EPS)
		{
			p ++;
			if(p > n)
				j ++, p = i;
		}
		if(j > n + 1)
			break;
		if(p != i)
			for(int k = 1; k <= n + 1; k ++)
			{
				double tmp = matrix[i][k];
				matrix[i][k] = matrix[p][k];
				matrix[p][k] = tmp;
			}
		double tmp = matrix[i][j];
		for(int k = 1; k <= n + 1; k ++)
			matrix[i][k] /= tmp;
		for(p = 1; p <= n; p ++)
			if(p != i && abs(matrix[p][j]) > EPS)
			{
				tmp = matrix[p][j] / matrix[i][j];
				for(int k = 1; k <= n + 1; k ++)
					matrix[p][k] -= tmp * matrix[i][k];
			}
	}
	for(int i = 1; i < n; i ++)
		printf("%.3lf ", matrix[i][n + 1]);
	printf("%.3lf\n", matrix[n][n + 1]);
}
