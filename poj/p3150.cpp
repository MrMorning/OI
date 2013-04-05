/*
 * Date: Mon Jan 31 22:01:23 CST 2011
 * Author: csimstu
 * Problem: poj3150
 * Algorithm: Compression && Matrix Multiplication
 */
#include <cstdio>
#include <cstring>
#define MAXL 511

typedef long long ll;

int n, modVal;

inline int abs(int x)
{
	return x > 0 ? x : -x;
}
inline int min(int a, int b)
{
	return a < b ? a : b;
}

struct Matrix
{
	ll ele[MAXL][MAXL];
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
	}
	void unfold()
	{
		for(int i = 1; i <= n; i ++)
		{
			ll tmp = ele[i][1];
			int x = i, y = 1;
			for(int t = 1; t <= n; t ++)
			{
				ele[x][y] = tmp;
				x = x % n + 1;
				y = y % n + 1;
			}
		}
	}
} facMatrix[25];

Matrix operator*(const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int i = 1; i <= n; i ++)
	{
		for(int k = 1; k <= n; k ++)
			c.ele[i][1] += a.ele[i][k] * b.ele[k][1];
		c.ele[i][1] %= modVal;
	}
	return c;
}

Matrix combine(const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= n; j ++)
		{
			int tmp = j + i - 2;
			if(tmp >= n) tmp -= n;
			tmp ++;
			c.ele[i][1] += a.ele[j][1] * b.ele[tmp][1];
		}
		c.ele[i][1] %= modVal;
	}
	return c;
}

int main()
{
	freopen("t.in", "r", stdin);
	int d, k;
	scanf("%d %d %d %d\n", &n, &modVal, &d, &k);
	Matrix initMatrix;
	for(int i = 1; i <= n; i ++)
		scanf("%lld", &initMatrix.ele[i][1]);
	for(int i = 1; i <= n; i ++)
		if(min(abs(i - 1), n - abs(i - 1)) <= d)
			facMatrix[1].ele[i][1] = 1;
#ifdef DEBUG
	facMatrix[1].debug();
	facMatrix[1].unfold();
	facMatrix[1].debug();
#endif
	for(int i = 2; i <= 24; i ++)
		facMatrix[i] = combine(facMatrix[i - 1], facMatrix[i - 1]);
	int cnt = 0;
	Matrix ansMatrix;
	ansMatrix.ele[1][1] = 1;

	while(k)
	{
		cnt ++;
		if(k & 1)
			ansMatrix = combine(ansMatrix, facMatrix[cnt]);
		k >>= 1;
	}
	ansMatrix.unfold();
	Matrix finalMatrix = ansMatrix * initMatrix;
	for(int i = 1; i <= n - 1; i ++)
		printf("%lld ", finalMatrix.ele[i][1]);
	printf("%lld\n", finalMatrix.ele[n][1]);
}


