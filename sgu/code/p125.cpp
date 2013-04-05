#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
const int offset[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int a[3][3], b[3][3];
int n;

bool fine(int i, int j)
{
	int cnt = 0;
	for(int d = 0; d < 4; d ++)
	{
		int ni = i + offset[d][0],
			nj = j + offset[d][1];
		if(0 <= ni && ni < n)
			if(0 <= nj && nj < n)
			{
				if(a[ni][nj] == -1)
					return true;
				cnt += a[ni][nj] > a[i][j];
			}
	}
	return cnt == b[i][j];
}

bool check(int i, int j)
{
	for(int r = 0; r <= i; r ++)
		for(int s = 0; s <= j; s ++)
			if(!fine(r, s))
				return false;
	return true;
}

void dfs(int i, int j)
{
	if(j == n)
		dfs(i + 1, 0);
	if(i == n)
	{
		for(int r = 0; r < n; r ++)
		{
			for(int s = 0; s < n - 1; s ++)
				printf("%d ", a[r][s]);
			printf("%d\n", a[r][n - 1]);
		}
		exit(0);
	}
	for(int k = 0; k < 10; k ++)
	{
		a[i][j] = k;
		if(check(i, j))
			dfs(i, j + 1);
		a[i][j] = -1;
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			scanf("%d", &b[i][j]);
	memset(a, -1, sizeof(a));
	dfs(0, 0);
	printf("NO SOLUTION\n");
}
