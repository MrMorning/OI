/*
 * Date :Mon Jan 31 15:56:54 CST 2011
 * Author: csimstu
 * Problem: poj 3735
 * Algorithm: Matrices Multiplication + Optimalization
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXL 110
typedef long long ll;
using std::cout;
struct Matrix
{
	int m, n;
	ll ele[MAXL][MAXL];
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
		m = n = 0;
	}
} stepMatrix[110], repMatrix[35];

int repTimes, catNum, stepNum;

Matrix operator* (const Matrix &a, const Matrix &b)
{
	if(a.n != b.m)
		printf("oche!!~~~");
	Matrix c;
	c.m = a.m, c.n = b.n;
	/*
	for(int i = 1; i <= c.m; i ++)
		for(int j = 1; j <= c.n; j ++)
			for(int k = 1; k <= a.n; k ++)
				if(a.ele[i][k] && b.ele[k][j])
					c.ele[i][j] += a.ele[i][k] * b.ele[k][j];
					*/
	for(int i = 1; i <= a.m; i ++)
		for(int j = 1; j <= a.n; j ++)
			if(a.ele[i][j])
				for(int k = 1; k <= b.n; k ++)
					c.ele[i][k] += a.ele[i][j] * b.ele[j][k];
	return c;
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%d %d %d\n", &catNum, &repTimes, &stepNum);
		if(repTimes == 0 && catNum == 0 && stepNum == 0)
			break;
		Matrix identityMatrix;
		identityMatrix.m = identityMatrix.n = catNum + 1;
		for(int i = 1; i <= catNum + 1; i ++)
			identityMatrix.ele[i][i] = 1;
		repMatrix[1] = identityMatrix;
		for(int i = 1; i <= stepNum; i ++)
		{
			stepMatrix[i] = identityMatrix;
			char ctrl;
			scanf("%c", &ctrl);
			if(ctrl == 'g')
			{
				int tmp;
				scanf("%d\n", &tmp);
				stepMatrix[i].ele[tmp][catNum + 1] = 1;
			}
			else if(ctrl == 's')
			{
				int a, b;
				scanf("%d %d\n", &a, &b);
				stepMatrix[i].ele[a][a] = stepMatrix[i].ele[b][b] = 0;
				stepMatrix[i].ele[a][b] = stepMatrix[i].ele[b][a] = 1;
			}
			else
			{
				int tmp;
				scanf("%d\n", &tmp);
				stepMatrix[i].ele[tmp][tmp] = 0;
			}
		}
		for(int i = stepNum; i >= 1; i --)
			repMatrix[1] = repMatrix[1] * stepMatrix[i];
		for(int i = 2; i <= 30; i ++)
			repMatrix[i] = repMatrix[i - 1] * repMatrix[i - 1];
		Matrix ansMatrix;
		ansMatrix.m = catNum + 1, ansMatrix.n = 1;
		ansMatrix.ele[catNum + 1][1] = 1;
		int cnt = 0;
		while(repTimes > 0)
		{
			cnt ++;
			if(repTimes & 1)
				ansMatrix = repMatrix[cnt] * ansMatrix;
			repTimes >>= 1;
		}
		for(int i = 1; i <= catNum - 1; i ++)
			cout << ansMatrix.ele[i][1] << ' ';
		cout << ansMatrix.ele[catNum][1] << '\n';
	}
}
