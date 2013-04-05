#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long bignum_t;
#define BIGNUM_T_FMT "%I64d"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_MAX = 1000010;

int prime[N_MAX], n_prime, coef[N_MAX];

bignum_t solve(int A, int B, int d)
{
	static bool is_prime[N_MAX];
	A /= d, B /=d ;
	int n = MIN(A, B);
	memset(is_prime, -1, sizeof(bool) * (n + 1));
	bignum_t ans = (bignum_t)A * B;
	coef[1] = 1;
	for(int i = 2; i <= n; i ++)
	{
		if(is_prime[i])
		{
			prime[n_prime ++] = i;
			coef[i] = -1;
		}
		ans += coef[i] * (bignum_t)(A / i) * (B / i); 
		for(int j = 0, upperlim = n / i; prime[j] <= upperlim; j ++)
		{
			is_prime[prime[j] * i] = false;
			if(i % prime[j] == 0)
			{
				coef[i * prime[j]] = 0;
				break;
			}
			else
				coef[i * prime[j]] = coef[i] * -1;
		}
	}
	return ans;
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int A, B, d;
	scanf("%d%d%d", &A, &B, &d);
	printf(BIGNUM_T_FMT "\n", solve(A, B, d));
}
