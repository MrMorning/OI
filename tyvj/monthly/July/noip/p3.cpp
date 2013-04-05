#include <cstdio>
typedef long long ll;
const int MOD_NUM = 1000000007;
int s, n, c;

int pow_mod(int a, int n)
{
	int ret = (n & 1) ? a : 1;
	n >>= 1;
	while(n)
	{
		a = (ll)a * a % MOD_NUM;
		if(n & 1)
			ret = (ll)ret * a % MOD_NUM;
		n >>= 1;
	}
	return ret;
}

int bino(int n, int k)
{
	int up = 1;
	for(int i = n - k + 1; i <= n; i ++)
		up = (ll)up * i % MOD_NUM;
	int down = 1;
	for(int i = 1; i <= k; i ++)
		down = (ll)down * i % MOD_NUM;
	return (ll)up * pow_mod(down, MOD_NUM - 2) % MOD_NUM;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &s, &n);
	for(int i = 0; i < n; i ++)
	{
		scanf("%d", &c);
		s -= c + 1;
	}
	printf("%d\n", bino(s + n - 1, n - 1));
}
