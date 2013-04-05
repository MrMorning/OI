/*
 * Date: Mon Jan 31 14:26:48 CST 2011
 * Author: csimstu
 * Problem: poj3070
 * Algorithm: Matrices Multiplization
 * Submission: A
 */
#include <cstdio>
#include <cstring>
#define MAXL 3
struct Matrix
{
	int ele[MAXL][MAXL], m, n;
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
		m = n = 0;
	}
} basicMatrix[31];
int n;

Matrix operator*(const Matrix &a, const Matrix &b)
{
	Matrix c;
	if(a.n != b.m)
		printf("oche!!");
	c.m = a.m, c.n = b.n;
	for(int i = 1; i <= c.m; i ++)
		for(int j = 1; j <= c.n; j ++)
			for(int k = 1; k <= a.n; k ++)
				c.ele[i][j] = (c.ele[i][j] + a.ele[i][k] * b.ele[k][j]) % 10000;
	return c;
}

int main()
{
	freopen("t.in", "r", stdin);
	basicMatrix[1].m = basicMatrix[1].n = 2;
	basicMatrix[1].ele[1][1] = basicMatrix[1].ele[1][2] = basicMatrix[1].ele[2][1] = 1;
	for(int i = 2; i <= 30; i ++)
		basicMatrix[i] = basicMatrix[i - 1] * basicMatrix[i - 1];
	while(1)
	{
		scanf("%d\n", &n);
		if(n == -1)
			break;
		int cnt = 0;
		Matrix matrixAcc;
		matrixAcc.m = matrixAcc.n = 2;
		matrixAcc.ele[1][1] = matrixAcc.ele[2][2] = 1;
		while(n > 0)
		{
			cnt ++;
			if(n & 1)
				matrixAcc = matrixAcc * basicMatrix[cnt];
			n >>= 1;
		}
		Matrix initMatrix;
		initMatrix.m = 2, initMatrix.n = 1;
		initMatrix.ele[1][1] = 1, initMatrix.ele[2][1] = 0;
		Matrix finalMatrix = matrixAcc * initMatrix;
		printf("%d\n", finalMatrix.ele[2][1]);
	}
}
