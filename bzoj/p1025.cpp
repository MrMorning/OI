#include <cstdio>
#include <cstring>
typedef long long ll;
int n, prime[1001], nPrime;
ll f[1001][1001];

ll dp(int i, int j)
{
	if(f[i][j] != -1)
		return f[i][j];
	if(i == 0)
		return f[i][j] = 1;
	f[i][j] = dp(i - 1, j);
	for(int x = prime[i]; x <= j; x *= prime[i])
		f[i][j] += dp(i - 1, j - x);	
	return f[i][j];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 2; i <= n; i ++)
	{
		bool isPrime = true;
		for(int j = 2; j * j <= i; j ++)
			if(i % j == 0)
			{
				isPrime = false;
				break;
			}
		if(isPrime)
			prime[++ nPrime] = i;
	}
	memset(f, -1, sizeof(f));
	printf("%lld\n", dp(nPrime, n));
}
