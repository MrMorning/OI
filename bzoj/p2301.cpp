#include <cstdio>
#include <algorithm>
typedef long long bignum_t;

const int N_MAX = 50010;

int sf[N_MAX][2], coef[N_MAX], prime[N_MAX];
int n_sf, n_prime;

void init()
{
	static bool not_prime[N_MAX];
	for(int i = 2; i < N_MAX; i ++)
	{
		if(! not_prime[i])
		{
			prime[n_prime ++] = i;
			coef[i] = -1;
		}
		if(coef[i] != 0)
		{
			sf[n_sf][0] = i, sf[n_sf][1] = coef[i];
			n_sf ++;
		}
		for(int j = 0, upperlim = (N_MAX - 1) / i; prime[j] <= upperlim; j ++)
		{
			int k = i * prime[j];
			not_prime[k] = true;
			if(i % prime[j] == 0)
			{
				coef[k] = 0;
				break;
			}
			else
				coef[k] = coef[i] * -1;
		}
	}
}

bignum_t solve(int a, int b, int k)
{
	a /= k, b /= k;
	int upperlim = std::max(a, b);
	bignum_t ans = (bignum_t)a * b;
	for(int i = 0; sf[i][0] <= upperlim; i ++)
		ans += (bignum_t)sf[i][1] * (a / sf[i][0]) * (b / sf[i][0]);
	return ans;

}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	init();
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
	{
		int a, b, c, d, k;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%I64d\n", solve(b, d, k) - solve(a - 1, d, k) - solve(b, c - 1, k) + solve(a - 1, c - 1, k));
	}
}
