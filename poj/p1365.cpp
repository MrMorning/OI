/*
 * Date: Tue Feb  1 09:57:04 CST 2011
 * Author: csimstu
 * Problem: poj1365
 * Algorithm: prime resolve
 */
#include <cstdio>
#include <cstring>
#define MAX_NUM 32767
#define PRIME_NUM 3512

int prime[PRIME_NUM + 1];

void initPrimes()
{
	bool hash[MAX_NUM + 1];
	memset(hash, 1, sizeof(hash));
	int primeCnt = 0;
	for(int i = 2; i <= MAX_NUM; i ++)
		if(hash[i])
		{
			prime[++ primeCnt] = i;
			for(int j = i; j <= MAX_NUM; j += i)
				hash[j] = false;
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	initPrimes();
	while(1)
	{
		int p, e;
		scanf("%d", &p);
		if(p == 0)
			break;
		scanf("%d", &e);
		int tmp = 1;
		while(e --)
			tmp *= p;
		char ch;
		while(scanf("%c", &ch), ch != '\n')
		{
			scanf("%d %d", &p, &e);
			while(e --)
				tmp *= p;
		}
		tmp --;
		int cnt[PRIME_NUM + 1];;
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1; i <= PRIME_NUM; i ++)
		{
			while(tmp % prime[i] == 0)
				cnt[i] ++, tmp /= prime[i];
		}
		int ans[PRIME_NUM * 2 + 1], ansNum = 0;
		for(int i = PRIME_NUM; i >= 1; i --)
			if(cnt[i] > 0)
				ans[++ ansNum] = prime[i], ans[++ ansNum] = cnt[i];
		for(int i = 1; i < ansNum; i ++)
			printf("%d ", ans[i]);
		printf("%d\n", ans[ansNum]);
	}
}
