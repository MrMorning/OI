/*
 * Date: Sat Jan 29 14:04:56 CST 2011
 * Author: csimstu
 * Problem: poj1830(开灯问题)
 * Algorithm: Search
 * Submission: TLE
 */ 
#include <cstdio>
#include <cstring>
#define MAXN 30

int ans = 0, testNum, n, k[MAXN][MAXN], a[MAXN], aTmp[MAXN], b[MAXN], x[MAXN];

void search(int i)
{
	if(i > n)
	{
		memcpy(aTmp, a, sizeof(a));
		for(int i = 1; i <= n; i ++)
			if(x[i] == 1)
				for(int j = 1; j <= n; j ++)
					if(k[i][j])
						a[j] ^= 1;
		bool suc = true;
		for(int i = 1; i <= n; i ++)
			if(a[i] != b[i])
			{
				suc = false;
				break;
			}
		if(suc)
			ans ++;
		memcpy(a, aTmp, sizeof(a));
		return;
	}
	search(i + 1);
	x[i] = 1;
	search(i + 1);
	x[i] = 0;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &testNum);
	while(testNum --)
	{
		ans = 0;
		memset(k, 0, sizeof(k));
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i ++)
			scanf("%d", &b[i]);
		while(1)
		{
			int i, j;
			scanf("%d %d", &i, &j);
			if(i == 0 && j == 0)
				break;
			k[i][j] = 1;
		}
		for(int i = 1; i <= n; i ++)
			k[i][i] = 1;
		search(1);
		if(ans == 0)
			printf("Oh,it's impossible~!!\n");
		else
			printf("%d\n", ans);
	}
}
