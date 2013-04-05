/*
 * Date: Sat Feb 12 21:25:08 CST 2011
 * Author: csimstu
 * Prob: poj2888 Polya Counting with restrictions
 * Algorithm: Polya Counting + Matrix Multiplication
 */
#include <cstdio>
#include <cstring>
#define MATRIX_LEN 11
#define DEBUG

struct Matrix
{
	int ele[MATRIX_LEN][MATRIX_LEN];
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
	}
} idMatrix, binMatrix[31];
int n, m;

Matrix operator*(const Matrix& A, const Matrix& B)
{
	Matrix C;
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j <= m; j ++)
		{
			for(int k = 1; k <= m; k ++)
				C.ele[i][j] += A.ele[i][k] * B.ele[k][j];
			C.ele[i][j] %= 9973;
		}
	return C;
}
Matrix pow(int times)
{
	int cnt = 0;
	Matrix A = idMatrix;
	while(times > 0)
	{
		cnt ++;
		if(times & 1)
			A = A * binMatrix[cnt];
		times >>= 1;
	}
	return A;
}

int euler(int x)
{
	int ans = 1;
	for(int i = 2; i * i <= x; i ++)
		if(x % i == 0)
		{
			ans *= i - 1;
			x /= i;
			while(x % i == 0)
			{
				ans *= i;
				x /= i;
			}
		}
	if(x > 1)
		ans *= x - 1;
	return ans;
}

int getTrail(int i)
{
	Matrix A = pow(i);
	int cnt = 0;
	for(int j = 1; j <= m; j ++)
		cnt = (cnt + A.ele[j][j]) % 9973;
	return cnt;
}

int main()
{
#ifdef DEBUG
	//printf("%d\n", euler(72));
#endif
	freopen("t.in", "r", stdin);
	for(int i = 1; i <= MATRIX_LEN; i ++)
		idMatrix.ele[i][i] = 1;
	binMatrix[0] = idMatrix;
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		for(int i = 1; i <= MATRIX_LEN; i ++)
			for(int j = 1; j <= MATRIX_LEN; j ++)
				binMatrix[1].ele[i][j] = 1;
		int k;
		scanf("%d %d %d\n", &n, &m, &k);
		for(int i = 1, a, b; i <= k; i ++)
		{
			scanf("%d %d\n", &a, &b);
			binMatrix[1].ele[a][b] = binMatrix[1].ele[b][a] = 0;
		}
		for(int i = 2; i <= 30; i ++)
			binMatrix[i] = binMatrix[i - 1] * binMatrix[i - 1];
		int ans = 0;
		for(int i = 1; i * i <= n; i ++)
			if(n % i == 0)
			{
				ans = (ans + getTrail(i) * (euler(n / i) % 9973)) % 9973;
				if(i * i != n)
					ans = (ans + getTrail(n / i) * (euler(i) % 9973)) % 9973;
			}
		int final;
		for(final = 1; ; final ++)
			if(((long long)n * final - ans) % 9973 == 0)
				break;
		printf("%d\n", final % 9973);
	}
}
