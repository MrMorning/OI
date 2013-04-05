#include <cstdio>
#include <cmath>
const int X_MAX = 1000000000;
const int SQRT_X_MAX = 31625;

int prime[31625], primeCnt;

void initPrimes()
{
	static bool notPrime[SQRT_X_MAX];
	for(int x = 2, upperlim = (int)sqrt(X_MAX); x <= upperlim; x ++)
		if(!notPrime[x])
		{
			prime[primeCnt ++] = x;
			for(int y = x + x; y <= upperlim; y += x)
				notPrime[y] = true;
		}
}

bool isPrime(int x)
{
	if(x == 1)
		return false;
	for(int i = 0; i < primeCnt; i ++)
		if(x != prime[i] && x % prime[i] == 0)
			return false;
	return true;
}

int main()
{
	freopen("t.in", "r", stdin);
	initPrimes();
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		int x;
		scanf("%d", &x);
		bool flag = false;
		for(int i = 0; i < primeCnt; i ++)
			if(x % prime[i] == 0 && isPrime(x / prime[i]))
			{
				flag = true;
				break;
			}
		printf("%s\n", flag ? "Yes" : "No");
	}
}
