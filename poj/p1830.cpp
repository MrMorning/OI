/*
 * Date: Sat Jan 29 15:24:36 CST 2011
 * Author: csimstu
 * Problem: poj1830 (Turning Lights off)
 * Algorithm: Gause Elimination
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 30

using std::swap;

int n, ans, a[MAXN], b[MAXN], m[MAXN][MAXN + 1];

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d", &testNum);
	while(testNum --)
	{
		memset(m, 0, sizeof(m));
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i ++)
			scanf("%d", &b[i]);
		for(int i = 1; i <= n; i ++)
			m[i][n + 1] = b[i] ^ a[i];
		while(1)
		{
			int i, j;
			scanf("%d %d", &i, &j);
			if(i == 0 && j == 0)
				break;
			m[j][i] = 1;
		}
		for(int i = 1; i <= n; i ++)
			m[i][i] = 1;
		//Gause Elimination
		int j = 1;
		for(int i = 1; i <= n; i ++)
		{
			int p = i;
			while(m[p][j] != 1 && j <= n + 1)
			{
				while(m[p][j] == 0 && p < n)
					p ++;
				if(m[p][j] == 1)
					break;
				j ++;
				p = i;
			}
			if(j > n + 1)
				break;
			//swap rows
			for(int k = 1; k <= n + 1; k ++)
				swap(m[p][k], m[i][k]);
			for(p = 1; p <= n; p ++)
				if(p != i && m[p][j] == 1)
					//substract row p from row i
					for(int k = j; k <= n + 1; k ++)
						m[p][k] ^= m[i][k];
			j ++;
		}
		bool suc = true;
		int cnt = 0;
		for(int p = n; p >= 1; p --)
		{
			int noneZeroCnt = 0;
			for(int k = 1; k <= n; k ++)
				if(m[p][k] != 0)
					noneZeroCnt ++;
			if(noneZeroCnt == 0 && m[p][n + 1] != 0)
			{
				suc = false;
				break;
			}
			if(noneZeroCnt > 0)
				cnt ++;
		}
		if(! suc)
			printf("Oh,it's impossible~!!\n");
		else
		{
			ans = 1;
			for(int i = 1; i <= n - cnt; i ++)
				ans *= 2;
			printf("%d\n", ans);
		}
	}
}
