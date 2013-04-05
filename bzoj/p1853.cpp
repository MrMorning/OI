#include <cstdio>
typedef long long bignum_t;
#define BIGNUM_T_FMT "%lld"

bignum_t ans, upperlim, max_luck;
int n_luck;
bignum_t luck[1000000];

void dfs(int i, bignum_t x, int flag)
{
	if(x > upperlim)
		return;
	if(x != 1)
		ans += flag * (upperlim / x);
	if(i == n_luck)
		return;
	dfs(i + 1, x, flag);
	dfs(i + 1, x * luck[i], flag * -1);
}

bignum_t calc(bignum_t n)
{
	ans = 0;
	upperlim = n;
	dfs(0, 1, -1);
	return ans;
}

void generate(bignum_t x, int cnt)
{
	if(x > max_luck)
		return;
	bool b = x % 1000 % 8 == 0;
	if(x && (x == 6 || x % 3) && (x < 1000 || ! b))
		luck[n_luck ++] = x;
	if(x >= 1000 && b)
		return;
	generate(x * 10 + 6, cnt + 6);
	generate(x * 10 + 8, cnt + 8);
}

int main()
{
	freopen("t.in", "r", stdin);
	bignum_t a, b;
	scanf(BIGNUM_T_FMT BIGNUM_T_FMT, &a, &b);
	max_luck = b;
	generate(0, 0);
	printf(BIGNUM_T_FMT "\n", calc(b) - calc(a - 1));
}
