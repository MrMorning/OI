#include <cstdio>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int n, k;
double f[102][1 << 15];
int w[16], s[16];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &k);
	for(int i = 0, t; i < k; i ++)
	{
		scanf("%d", &w[i]);
		scanf("%d", &t);
		while(t)
		{
			s[i] += 1 << (t - 1);
			scanf("%d", &t);
		}
	}

	for(int i = n; i >= 1; i --)
		for(int j = 0; j < (1 << k); j ++)
		{
			f[i][j] = 0;
			for(int t = 0; t < k; t ++)
				if((s[t] & j) == s[t])
					f[i][j] += MAX(f[i + 1][j], f[i + 1][j | (1 << t)] + w[t]);
				else
					f[i][j] += f[i + 1][j];
			f[i][j] /= (double)k;
		}
	printf("%.6lf\n", f[1][0]);
}
