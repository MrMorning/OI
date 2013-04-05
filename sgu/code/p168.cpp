#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, f[1002][1002];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d", &f[i][j]);
	for(int j = m; j >= 1; j --)
		for(int i = n; i >= 1; i --)
			f[i][j] = min(f[i][j], min(f[i + 1][j], min(f[i][j + 1], f[i - 1][j + 1])));
	for(int i = 1; i <= n; i ++, printf("\n"))
		for(int j = 1; j <= m; j ++)
			printf("%d ", f[i][j]);
}
