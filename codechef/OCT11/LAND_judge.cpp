#include <cstdio>
#include <cstdlib>
#include <cmath>
double a[100][100];
int n, m;

int main()
{
	FILE *fres = fopen("t.out", "r");
	FILE *fdata = fopen("t.in", "r");
	int _;
	fscanf(fdata, "%d", &_);
	double ans = 0;
	for(int ti = 0; ti < _; ti ++)
	{
		fscanf(fdata, "%d%d", &n, &m);
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < m; j ++)
				fscanf(fres, "%lf", &a[i][j]);
		for(int i = 0; i < n; i ++)
			for(int j = 0, tmp; j < m; j ++)
				fscanf(fdata, "%d", &tmp);
		double res = 0;
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < m; j ++)
			{
				if(i + 1 < n)
					res += pow(2, fabs(a[i][j] - a[i + 1][j])); 
				if(j + 1 < m)
					res += pow(2, fabs(a[i][j] - a[i][j + 1])); 
			}
		res = log(res) / log(2);
		ans += res;
	}
	fprintf(stderr, "%.6lf\n", ans / _);
}
