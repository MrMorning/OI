#include <cstdio>
#include <cstring>
#define MAXL 51

struct Matrix
{
	int ele[MAXL][MAXL];
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
	}
	void print()
	{
		for(int i = 1; i <= 20; i ++)
		{
			for(int j = 1; j <= 20; j ++)
				printf("%d ", ele[i][j]);
			printf("\n");
		}
	}
} facMatrix[29], strictMatrix[13], basicMatrix;
int n, m, k, st, en, fishNum;

Matrix operator* (const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(a.ele[i][j])
				for(int k = 1; k <= n; k ++)
					c.ele[i][k] = (c.ele[i][k] + a.ele[i][j] * b.ele[j][k]) % 10000;
	return c;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d %d %d\n", &n, &m, &st, &en, &k);
	st ++, en ++;
	for(int i = 1, x, y; i <= m; i ++)
	{
		scanf("%d %d\n", &x, &y);
		x ++, y ++;
		basicMatrix.ele[x][y] = basicMatrix.ele[y][x] = 1;
	}
	scanf("%d\n", &fishNum);
	for(int i = 1; i <= 12; i ++)
		for(int j = 1; j <= n; j ++)
			strictMatrix[i].ele[j][j] = 1;
	for(int i = 1, t; i <= fishNum; i ++)
	{
		scanf("%d", &t);
		int p[5];
		for(int i = 1; i <= t; i ++)
		{
			scanf("%d", &p[i]);
			p[i] ++;
		}
		int cnt = 1;
		while(cnt < 12)
		{
			for(int l = 1; l <= t; cnt ++, l ++)
				strictMatrix[cnt].ele[p[l]][p[l]] = 0;
		}
	}
	for(int i = 1; i <= n; i ++)
		facMatrix[1].ele[i][i] = 1;
	for(int i = 1; i <= 12; i ++)
		facMatrix[1] = facMatrix[1] * basicMatrix * strictMatrix[i % 12 + 1];
	for(int i = 2; i <= 28; i ++)
		facMatrix[i] = facMatrix[i - 1] * facMatrix[i - 1];
	int tmp = k / 12;
	int cnt = 0;
	Matrix ansMatrix;
	for(int i = 1; i <= n; i ++)
		ansMatrix.ele[i][i] = 1;
	
	while(tmp)
	{
		cnt ++;
		if(tmp & 1)
			ansMatrix = ansMatrix * facMatrix[cnt];
		tmp >>= 1;
	}
	k %= 12;
	for(int i = 1; i <= k; i ++)
	{
		ansMatrix = ansMatrix * basicMatrix * strictMatrix[i % 12 + 1];
	}
	printf("%d\n", ansMatrix.ele[st][en]);
}
