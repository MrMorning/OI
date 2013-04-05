#include <cstdio>
#include <algorithm>
using namespace std;
int n, m;
double f[2][5001];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= m; j ++)
			f[i & 1][j] = max((double)0, (i ? (f[!(i & 1)][j] + 1) * i / (i + j) : 0) + (j ? (f[i & 1][j - 1] - 1) * j / (i + j) : 0));
	printf("%.6lf\n", (int)(f[n & 1][m] * 1E6) / 1E6);
}
