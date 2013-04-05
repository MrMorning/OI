#include <cstdio>
const int oo = 0x3f3f3f3f;
int n, m, w[110][110], f[110][110], g[110][110];

void output(int i, int j)
{
	if(i == 0)
		return;
	if(g[i][j] == 1)
	{
		output(i - 1, j - 1);
		printf("%d ", i);
	}
	else
		output(i - 1, j);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d", &w[i][j]);
	f[0][0] = 0;
	for(int i = 1; i <= m; i ++)
	{
		f[i][0] = 0;
		for(int j = 1; j <= i; j ++)
		{
			if(j <= i - 1)
				f[i][j] = f[i - 1][j];
			else
				f[i][j] = -oo;
			int tmp = f[i - 1][j - 1] + w[j][i];
			if(tmp > f[i][j])
				f[i][j] = tmp, g[i][j] = 1;
		}
	}
	printf("%d\n", f[m][n]);
	output(m, n);
}
