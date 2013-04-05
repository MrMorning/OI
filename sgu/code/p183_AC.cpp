#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int oo = 0x3f3f3f3f;
int n, m;
int c[10010], f[2][110][110];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &c[i]);
	f[0][0][0] = 0;
	int now = 0;
	for(int i = 0; i < n; i ++, now ^= 1)
	{
		memset(f[now ^ 1], 0x3f, sizeof(f[now ^ 1]));
		for(int j = 0; j < m; j ++)
			for(int k = j; k < m; k ++)
				if(f[now][j][k] != oo)
				{
					if(j + 1 <= m - 1)
						f[now ^ 1][0][j + 1] = min(f[now ^ 1][0][j + 1], f[now][j][k] + c[i + 1]);
					if(k + 1 <= m - 1)
						f[now ^ 1][j + 1][k + 1] = min(f[now ^ 1][j + 1][k + 1], f[now][j][k]);
				}
	}
	int ans = oo;
	for(int j = 0; j < m; j ++)
		for(int k = j; k < m; k ++)
			ans = min(ans, f[now][j][k]);
	printf("%d\n", ans);
}
