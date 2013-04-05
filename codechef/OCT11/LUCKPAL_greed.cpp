#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const char LUCKPAL[2][10] = {"luckykcul", "ykculucky"};
const int N_MAX = 1010;
char str[N_MAX], curStr[N_MAX], ansStr[N_MAX];
int ans;

void solve()
{
	scanf("%s", str);
	int n = strlen(str);
	if(n < 9)
	{
		printf("unlucky\n");
		return;
	}
	ans = 0x3f3f3f3f;
	for(int ct = 0; ct < 2; ct ++)
	{
		for(int i = 0; i + 4 < (n + 1) / 2; i ++)
		{
			strcpy(curStr, str);
			int res = 0;
			for(int k = i; k < i + 5; k ++)
			{
				if(curStr[k] != LUCKPAL[ct][k - i])
					curStr[k] = LUCKPAL[ct][k - i], res ++;
				if(curStr[n - k - 1] != LUCKPAL[ct][k - i])
					curStr[n - k - 1] = LUCKPAL[ct][k - i], res ++;
			}
			for(int k = 0; k <= n / 2; k ++)
				if(curStr[k] != curStr[n - k - 1])
					curStr[k] = curStr[n - k - 1] = min(curStr[k], curStr[n - k - 1]), res ++;
			if(res < ans || (res == ans && strcmp(curStr, ansStr) < 0))
				ans = res, strcpy(ansStr, curStr);
		}
	}
	printf("%s %d\n", ansStr, ans);
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
