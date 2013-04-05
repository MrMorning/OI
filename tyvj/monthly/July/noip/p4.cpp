#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, a[1510][1510], f[2][1510][1510], ans[2];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &a[i][j]);
			if((i + j) % 2)
				a[i][j] ^= 1;
		}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			int t = a[i][j];
			f[t][i][j] = min(f[t][i - 1][j], min(f[t][i][j - 1], f[t][i - 1][j - 1])) + 1;
			ans[t] = max(ans[t], f[t][i][j]);
		}
	printf("%d\n", max(ans[0], ans[1]));
}
