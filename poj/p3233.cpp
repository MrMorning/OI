/*
 * Date: Mon Jan 31 15:02:49 CST 2011
 * Author: csimstu
 * Problem: poj3233
 * Algorithm: 矩阵快速幂+二分
 */
#include <cstdio>
#include <cstring>
#define MAXL 35

struct Matrix
{
	int ele[MAXL][MAXL];
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
	}
} binMatrix[35];

int n, target, modNum;

Matrix operator* (const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 1; k <= n; k ++)
				c.ele[i][j] = (c.ele[i][j] + a.ele[i][k] * b.ele[k][j] % modNum) % modNum;
	return c;
}

Matrix operator+ (const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			c.ele[i][j] = (a.ele[i][j] + b.ele[i][j]) % modNum;
	return c;
}

Matrix getMatrix(int k)
{
	int cnt = 0;
	Matrix matrixTmp;
	for(int i = 1; i <= n; i ++)
		matrixTmp.ele[i][i] = 1;
	while(k > 0)
	{
		cnt ++;
		if(k & 1)
			matrixTmp = matrixTmp * binMatrix[cnt];
		k >>= 1;
	}
	return matrixTmp;
}

Matrix sum(int k)
{
	if(k == 1)
		return binMatrix[1];
	Matrix matrixTmp = sum(k >> 1);
	matrixTmp = matrixTmp + (getMatrix(k >> 1) * matrixTmp);
	if(k & 1)
		matrixTmp = matrixTmp + getMatrix(k);
	return matrixTmp;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d\n", &n, &target, &modNum);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
		{
			scanf("%d", &binMatrix[1].ele[i][j]);
			binMatrix[1].ele[i][j] %= modNum;
		}
	for(int i = 2; i <= 30; i ++)
		binMatrix[i] = binMatrix[i - 1] * binMatrix[i - 1];
	Matrix ansMatrix = sum(target);
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= n - 1; j ++)
			printf("%d ", ansMatrix.ele[i][j]);
		printf("%d\n", ansMatrix.ele[i][n]);
	}
}
