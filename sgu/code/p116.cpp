#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
const int N_MAX = 10011;
const int PRIME_MAX = 1230;
const int SUPER_MAX = 211;

int prime[PRIME_MAX], super[SUPER_MAX];
int f[N_MAX];
int ans[N_MAX];
int primeCnt, superCnt;

void initPrimes()
{
	static bool notprime[N_MAX];
	for(int i = 2; i < N_MAX; i ++)
		if(!notprime[i])
		{
			prime[primeCnt ++] = i;
			for(int x = i + i; x < N_MAX; x += i)
				notprime[x] = true;
		}
}

void initSuperPrimes()
{
	for(int i = 0; prime[i] < primeCnt; i ++)
		super[superCnt ++] = prime[prime[i] - 1];
}
bool cmp(const int &a, const int &b)
{
	return a > b;
}
int main()
{
	freopen("t.in", "r", stdin);
	initPrimes();
	initSuperPrimes();
	int n;
	scanf("%d", &n);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for(int i = 1; i <= superCnt; i ++)
		for(int j = super[i - 1]; j <= n; j ++)
			if(f[j - super[i - 1]] + 1 < f[j])
				f[j] = f[j - super[i - 1]] + 1;
	if(f[n] == 0x3f3f3f3f)
	{
		printf("0\n");
		return 0;
	}
	printf("%d\n", f[n]);
	int cur = n;
	int ansCnt = 0;
	for(int i = superCnt; i >= 1; i --)
		while(cur >= super[i - 1] && f[cur] == f[cur - super[i - 1]] + 1)
		{
			ans[ansCnt ++] = super[i - 1];
			cur -= super[i - 1];
		}
	sort(ans, ans + ansCnt, cmp);
	for(int i = 0; i < ansCnt - 1; i ++)
		printf("%d ", ans[i]);
	printf("%d\n", ans[ansCnt - 1]);
}
