#include <cstdio>
int n;
bool notprime[1000001];
int prime[100000], primeCnt;
int ans[100000][2], ansCnt;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	notprime[0] = notprime[1] = true;
	for(int x = 2; x <= n; x ++)
		if(!notprime[x])
		{
			prime[primeCnt ++] = x;
			for(int y = x + x; y <= n; y += x)
				notprime[y] = true;
		}
	for(int i = 0; i <= 0; i ++)
		for(int j = i + 1; j < primeCnt; j ++)
		{
			int x = prime[i] + prime[j];
			if(x > n)
				continue;
			if(!notprime[x])
			{
				ans[ansCnt][0] = prime[i];
				ans[ansCnt][1] = prime[j];
				ansCnt ++;
			}
		}
	printf("%d\n", ansCnt);
	for(int i = 0; i < ansCnt; i ++)
		printf("%d %d ", ans[i][0], ans[i][1]);
}
