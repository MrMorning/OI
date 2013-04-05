#include <cstdio>
#include <cstring>
#define MAXM 21
int n, m, modNum, T[MAXM], pre[MAXM];
struct Matrix
{
	int ele[MAXM][MAXM];
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
	}
} ansMatrix, facMatrix[31];
Matrix operator* (const Matrix &a, const Matrix &b)
{
	Matrix c;
	for(int i = 0; i < m; i ++)
		for(int j = 0; j < m; j ++)
		{
			for(int k = 0; k < m; k ++)
				c.ele[i][j] += a.ele[i][k] * b.ele[k][j];
			c.ele[i][j] %= modNum;
		}
	return c;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d\n", &n, &m, &modNum);
	for(int i = 1; i <= m; i ++)
	{
		char ch;
		scanf("%c", &ch);
		T[i] = ch - '0';
	}
	pre[1] = 0;
	int j = 0;
	for(int i = 2; i <= m; i ++)
	{
		while(j > 0 && T[j + 1] != T[i])
			j = pre[j];
		if(T[j + 1] == T[i])
			j ++;
		pre[i] = j;
	}
	for(int j = 0; j < m; j ++)
		for(int x = 0; x <= 9; x ++)
		{
			if(x == T[j + 1])
				//next[j + 1][++ next[j + 1][0]] = j;
				facMatrix[1].ele[j+1][j] ++;
			else
			{
				int k = j;
				while(x != T[k + 1] && k > 0)
					k = pre[k];
				if(x == T[k + 1])
					//next[k + 1][++ next[k + 1][0]] = j;
					facMatrix[1].ele[k+1][j] ++;
				else
					//next[0][++ next[0][0]] = j;
					facMatrix[1].ele[0][j] ++;
			}
		}		
	for(int i = 2; i <= 30; i ++)
		facMatrix[i] = facMatrix[i - 1] * facMatrix[i - 1];
	ansMatrix.ele[0][0] = 1;
	int cnt = 0;
	while(n > 0)
	{
		cnt ++;
		if(n & 1)
			ansMatrix = facMatrix[cnt] * ansMatrix;
		n >>= 1;
	}
	//f[0][0] = 1;
	//for(int i = 1; i <= n; i ++)
	//	for(int j = 0; j < m; j ++)
	//		for(int k = 1; k <= next[j][0]; k ++)
	//			f[i][j] = (f[i][j] + f[i - 1][next[j][k]]) % modNum;
	int ans = 0;
	for(int j = 0; j < m; j ++)
		ans = (ans + ansMatrix.ele[j][0]) % modNum;
	printf("%d\n", ans);
}
