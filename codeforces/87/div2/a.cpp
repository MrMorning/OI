#include <cstdio>
#include <algorithm>
using namespace std;
int n;
int main()
{
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int res = 0;
	int ans = 0;
	for(int i = 0; i < n; i ++)
	{
		ans = max(ans, res);
		int a, b;
		scanf("%d%d", &a, &b);
		res -= a, res += b;
	}
	ans = max(ans, res);
	printf("%d\n", ans);
}
