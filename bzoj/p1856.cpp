#include <cstdio>
#include <iostream>
const int MOD_NUM = 20100403;
typedef long long val_t;
val_t powmod(val_t x, int n)
{
	val_t ret = (n & 1) ? x : 1;
	n >>= 1;
	while(n)
	{
		x = x * x % MOD_NUM;
		if(n & 1)
			ret = ret * x % MOD_NUM;
		n >>= 1;
	}
	return ret;
}
val_t calc_binomial(int n, int k)
{
	val_t ret = 1;
	for(int i = k + 1; i <= n; i ++)
		ret = ret * i % MOD_NUM;
	val_t tmp = 1;
	for(int i = 1; i <= n - k; i ++)
		tmp = tmp * i % MOD_NUM;
	ret = ret * powmod(tmp, MOD_NUM - 2) % MOD_NUM;
	return ret;
}
int main()
{
	int n, m;
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	val_t ans = calc_binomial(m + n, m) - calc_binomial(m + n, m - 1);
	if(ans < 0) ans += MOD_NUM;
	std::cout << ans;
}
