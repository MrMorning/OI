#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 101, M = 1000;
int svtx;
double p, inf = 1e100;
double f[2][N][N], w[N];
int n, m;
void clear(int now)
{ 
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			f[now][i][j] = -inf;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i ++)
		scanf("%lf", &w[i]);
	w[n ++] = 0;
	scanf("%d%lf", &svtx, &p); svtx --;
	clear(0);
	for (int a, b; m --; f[0][a][b] = w[a])
		scanf("%d%d", &a, &b), a --, b --;
	for (int i = 0; i < n; i ++)
		f[0][i][n - 1] = w[i];
	int now = 0, prev = 1;
	int niter = 25;
	while (niter --)
	{
		now ^= 1, prev ^= 1;
		clear(now);
		for (int k = 0; k < n; k ++)
			for (int i = 0; i < n; i ++)
				for (int j = 0; j < n; j ++)
					f[now][i][j] = max(f[now][i][j], f[prev][i][k] + f[prev][k][j] * p);
		p *= p;
	}
	double ans = 0;
	for (int i = 0; i < n; i ++)
		ans = max(ans, f[now][svtx][i]);
	printf("%.1lf\n", ans);
	return 0;
}
