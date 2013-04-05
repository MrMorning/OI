#include <cstdio>

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans += n / i;
	printf("%d\n", ans);
}
