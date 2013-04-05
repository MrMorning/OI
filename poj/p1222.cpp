/*
 * Date: Sat Jan 29 16:30:47 CST 2011
 * Author: csimstu
 * Problem: poj1222 EXTENDED LIGHTS OUT
 * Algorithm: Gause Elimination
 */ 
#include <cstdio>
#include <cstring>

int testNum, m[31][32], ans[6][7];

inline int get(int i, int j)
{
	return 6 * (i - 1) + j;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &testNum);
	for(int testCnt = 1; testCnt <= testNum; testCnt ++)
	{
		memset(m, 0, sizeof(m));
		for(int i = 1; i <= 5; i ++)
			for(int j = 1; j <= 6; j ++)
			{
				int t;
				scanf("%d", &t);
				m[get(i, j)][31] = t;
				m[get(i, j)][get(i, j)] = 1;
				if(i > 1)
					m[get(i - 1, j)][get(i, j)] = 1;
				if(i < 5)
					m[get(i + 1, j)][get(i, j)] = 1;
				if(j > 1)
					m[get(i, j - 1)][get(i, j)] = 1;
				if(j < 6)
					m[get(i, j + 1)][get(i, j)] = 1;
			}
		//Gause Elimination
		int j = 1;
		for(int i = 1; i <= 30; i ++)
		{
			int p;
			bool suc = false;
			while(! suc && j <= 31)
			{
				for(p = i; p <= 30; p ++)
					if(m[p][j] == 1)
					{
						suc = true;
						break;
					}
				if(suc)
					break;
				j ++;
			}
			if(j > 31)
				break;
			//swap row i and row p
			for(int k = 1; k <= 31; k ++)
			{
				int tmp = m[i][k];
				m[i][k] = m[p][k];
				m[p][k] = tmp;
			}
			for(p = 1; p <= 30; p ++)
				if(p != i && m[p][j] == 1)
					for(int k = 1; k <= 31; k ++)
						m[p][k] ^= m[i][k];
			j ++;
		}
		for(int i = 1; i <= 30; i ++)
		{
			int x = (i - 1) / 6 + 1;
			int y = i - 6 * (x - 1);
			ans[x][y] = m[i][31];
		}
		printf("PUZZLE #%d\n", testCnt);
		for(int i = 1; i <= 5; i ++)
		{
			for(int j = 1; j <= 5; j ++)
				printf("%d ", ans[i][j]);
			printf("%d\n", ans[i][6]);
		}
	}
}
