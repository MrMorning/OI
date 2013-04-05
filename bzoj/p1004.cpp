/*
 * Date: Thu Feb 17 16:20:47 CST 2011
 * Author: csimstu
 * Prob: hnoi2008 cards
 * Sol: Burnside Theorem + DP
 */
#include <cstdio>
#include <cstring>
#define MAXN 65
int n[4], m, modNum, perm[MAXN][MAXN], c[MAXN], f[MAXN][MAXN][MAXN], hash[MAXN];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d %d %d\n", &n[1], &n[2], &n[3], &m, &modNum);
	n[0] = n[1] + n[2] + n[3];
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j <= n[0]; j ++)
			scanf("%d", &perm[i][j]);
	m ++;
	for(int j = 1; j <= n[0]; j ++)
		perm[m][j] = j;
	int ans = 0;
	for(int i = 1; i <= m; i ++)
	{
		memset(hash, 0, sizeof(hash));
		memset(f, 0, sizeof(f));
		int objNum = 0;
		for(int j = 1; j <= n[0]; j ++)
			if(! hash[j])
			{
				hash[j] = true;
				int next = perm[i][j], cnt = 1;
				while(! hash[next])
				{
					hash[next] = true;
					cnt ++;
					next = perm[i][next];
				}
				c[++ objNum] = cnt;
			}
		f[0][0][0] = 1;
		for(int i = 1; i <= objNum; i ++)
			for(int j = 0; j <= n[1]; j ++)
				for(int k = 0; k <= n[2]; k ++)
				{
					f[i][j][k] = f[i - 1][j][k];
					if(j >= c[i])
						f[i][j][k] = (f[i][j][k] + f[i - 1][j - c[i]][k]) % modNum;
					if(k >= c[i])
						f[i][j][k] = (f[i][j][k] + f[i - 1][j][k - c[i]]) % modNum;
				}
		ans = (ans + f[objNum][n[1]][n[2]]) % modNum;
	}
	int k;
	for(k = 0; (k * modNum + ans) % m != 0; k ++);
	printf("%d\n", (k * modNum + ans) / m);
}
