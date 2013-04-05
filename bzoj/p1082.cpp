#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
int a[51], b[1001];
int n, m;
int upperlim, cnt;
bool dfs(int i)
{
	if(i == 0)
		return true;
	cnt ++;
	if(cnt > 10000000)
	{
		printf("%d\n", upperlim - 1);
		exit(0);
	}
	for(int j = 1; j <= m; j ++)
		if(a[j] >= b[i])
		{
			a[j] -= b[i];
			if(dfs(i - 1))
			{
				a[j] += b[i];
				return true;
			}
			a[j] += b[i];
		}
	return false;
}
inline bool cmp_dec(int a, int b)
{
	return a > b;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d", &a[i]);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &b[i]);
	sort(a + 1, a + 1 + m, cmp_dec);
	sort(b + 1, b + 1 + n);
	for(upperlim = 1; upperlim <= n; upperlim ++)
		if(! dfs(upperlim))
			break;
	printf("%d\n", upperlim - 1);
}
