#include <cstdio>
#include <cstring>
#define MAX_PRIME_NUM 2000
#define MAX_NUM 10000
int prime[MAX_PRIME_NUM + 1], sum[MAX_PRIME_NUM + 1], isPrime[MAX_NUM + 1];
int primeCnt;

void initPrime()
{
	memset(isPrime, 1, sizeof(isPrime));
	for(int i = 2; i <= MAX_NUM; i ++)
		if(isPrime[i])
		{
			prime[++ primeCnt] = i;
			for(int j = i * 2; j <= MAX_NUM; j += i)
				isPrime[j] = false;
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	initPrime();
	sum[0] = 0;
	for(int i = 1; i <= primeCnt; i ++)
		sum[i] = sum[i - 1] + prime[i];
	while(1)
	{
		int x;
		scanf("%d", &x);
		if(x == 0)
			break;
		int ans = 0;
		for(int i = 1; i <= primeCnt; i ++)
		{
			int l = 1, r = i, mid = (l + r) / 2;
			while(l <= r)
			{
				int tmp = sum[i] - sum[mid - 1];
				if(tmp < x)
					r = mid - 1;
				else if(tmp > x)
					l = mid + 1;
				else
				{
					ans ++;
					break;
				}
				mid = (l + r) / 2;
			}
		}
		printf("%d\n", ans);
	}
}
