#include <cstdio>
#include <cstring>

bool isPrime[10001];
bool suc, used[1001];
int ans[1001], s, t, d, n;

void initPrime()
{
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	for(int i = 1; i <= 100; i ++)
	{
		if(isPrime[i])
		{
			for(int j = i * 2; j <= 10000; j += i)
				isPrime[j] = false;
		}
	}
}

void search(int i)
{
	if(suc)
		return;
	if(i > 2)
	{
		int sum = ans[i - 1];
		for(int k = i - 2; k >= i - d; k --)
		{
			sum += ans[k];
			if(isPrime[sum])
				return;
		}
	}
	if(i > n)
	{
		for(int k = 1; k < n; k ++)
			printf("%d,", ans[k]);
		printf("%d\n", ans[n]);
		suc = true;
		return;
	}
	for(int k = s; k <= t; k ++)
		if(! used[k])
		{
			used[k] = true;
			ans[i] = k;
			search(i + 1);
			used[k] = false;
			ans[i] = 0;
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	initPrime();
	while(1)
	{
		scanf("%d %d %d\n", &s, &t, &d);
		if(s == 0)
			break;
		suc = false;
		n = t - s + 1;
		for(int i = s; i <= t; i ++)
			used[i] = false;
		search(1);
		if(! suc)
			printf("No anti-prime sequence exists.\n");
	}
}
