#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

int base, n, ans[2000][2000], a[2000];
int ansCnt;

void dfs(int idx, int sum)
{
	if(idx == n)
	{
		if(n == 1 || a[idx - 1])
		{
			memcpy(ans[ansCnt], a, sizeof(int) * n);
			ansCnt ++;
		}	
	}
	else
	{
		for(int d = 0; d < base; d ++)
		{
			a[idx] = d;
			int tmp = 0;
			for(int k = 0; k <= idx; k ++)
				tmp += a[k] * a[idx - k];
			if((tmp + sum) % base == d)
				dfs(idx + 1, (tmp + sum) / base);
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &base, &n);
	dfs(0, 0);
	printf("%d\n", ansCnt);
	for(int i = 0; i < ansCnt; i ++)
	{
		for(int j = n - 1; j >= 0; j --)
			printf("%c", (ans[i][j] > 9 ? 'A' + ans[i][j] - 10 : '0' + ans[i][j]));
		printf("\n");
	}
}
