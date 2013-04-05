#include <cstdio>
int n, m, k;
int ans;
int powMod(int a, int n)
{
	a %= k;
	int res = n & 1 ? a : 1;
	for(n >>= 1; n; n >>= 1)
	{
		a = a * a % k;
		if(n & 1)
			res = res * a % k;
	}
	return res;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < n; i ++)
	{
		int x;
		scanf("%d", &x);
		if(powMod(x, m) == 0)
			ans ++;
	}
	printf("%d\n", ans);
}
