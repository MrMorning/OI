/*
 * Date: Sat Jan 29 19:19:09 CST 2011
 * Author: csimstu
 * Problem: poj2947
 * Algorithm: 解线性同余方程
 * Submission: A
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MAXN 310
int n, m, matrix[MAXN][MAXN];
int ans[MAXN], ansNum;

int gcd(int a, int b)
{
	if(b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}

inline int mod7(int x)
{
	return (x + 7777777) % 7;
}

int weekMap(char* s)
{
	if(strcmp(s, "MON") == 0)
		return 1;
	else if(strcmp(s, "TUE") == 0)
		return 2;
	else if(strcmp(s, "WED") == 0)
		return 3;
	else if(strcmp(s, "THU") == 0)
		return 4;
	else if(strcmp(s, "FRI") == 0)
		return 5;
	else if(strcmp(s, "SAT") == 0)
		return 6;
	else if(strcmp(s, "SUN") == 0)
		return 7;
	return -1;
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%d %d\n", &n, &m);
		if(n == 0 && m == 0)
			break;
		memset(matrix, 0, sizeof(matrix));
		for(int i = 1; i <= m; i ++)
		{
			int k;
			char s1[5], s2[5];
			scanf("%d %s %s\n", &k, s1, s2);
			matrix[i][n + 1] = mod7(weekMap(s2) - weekMap(s1) + 1);
			int hash[MAXN];
			memset(hash, 0, sizeof(hash));
			for(int j = 1, t; j <= k; j ++)
			{
				scanf("%d", &t);
				hash[t] ++;
			}
			for(int k = 1; k <= n; k ++)
				matrix[i][k] = mod7(hash[k]);
		}
		int j = 1;
		for(int i = 1; i <= m; i ++)
		{
			bool suc = false;
			int p;
			while(! suc && j <= n + 1)
			{
				for(p = i; p <= m; p ++)
					if(matrix[p][j] != 0)
					{
						suc = true;
						break;
					}
				if(suc)
					break;
				j ++;
			}
			if(j > n + 1)
				break;
			if(i != p)
				for(int k = 1; k <= n + 1; k ++)
				{
					int tmp = matrix[i][k];
					matrix[i][k] = matrix[p][k];
					matrix[p][k] = tmp;
				}
			for(p = 1; p <= m; p ++)
				if(p != i && matrix[p][j] != 0)
				{
					int lcmTmp = lcm(matrix[p][j], matrix[i][j]);
					int tmp = lcmTmp / matrix[p][j];
					for(int k = n + 1; k >= 1; k --)
						matrix[p][k] = mod7(matrix[p][k] * tmp);
					int l = lcmTmp / matrix[i][j];
					for(int k = n + 1; k >= j; k --)
						matrix[p][k] = mod7(matrix[p][k] - l * matrix[i][k]);
				}
			j ++;
		}//end elimination
		int noneZeroCnt = 0;
		bool failed = false;
		for(int i = m; i >= 1; i --)
		{
			int cnt = 0;
			for(int j = 1; j <= n; j ++)
				if(matrix[i][j] != 0)
					cnt ++;
			if(cnt == 0 && matrix[i][n + 1] != 0)
			{
				failed = true;
				break;
			}
			if(cnt > 0)
				noneZeroCnt ++;
		}
		if(failed)
			printf("Inconsistent data.\n");
		else if(noneZeroCnt < n)
			printf("Multiple solutions.\n");
		else
		{
			ansNum = 0;
			for(int i = 1; i <= n; i ++)
			{
				int k = matrix[i][i], l = matrix[i][n + 1];
				bool flag = false;
				for(int x = 3; x <= 9; x ++)
					if((k * x - l + 7) % 7 == 0)
					{
						if(! flag)
						{
							ans[++ ansNum] = x;
							flag = true;
						}
						else
						{
							printf("Multiple solutions.\n");
							exit(0);
						}
					}
			}
			for(int i = 1; i < ansNum; i ++)
				printf("%d ", ans[i]);
			printf("%d\n", ans[ansNum]);
		}
	}
}
