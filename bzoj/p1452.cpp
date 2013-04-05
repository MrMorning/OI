#include <cstdio>
#define LOWBIT(x) (x & (-(x)))
const int N_MAX = 301, N_COL = 101;
int matrix[N_MAX][N_MAX];
int tree[N_MAX][N_MAX][N_COL];

int sum(int x, int y, int c)
{
	int ret = 0;
	for(int i = x; i; i -= LOWBIT(i))
		for(int j = y; j; j -= LOWBIT(j))
			ret += tree[i][j][c];
	return ret;
}

int ask(int x1, int y1, int x2, int y2, int c)
{
	return sum(x2, y2, c) - sum(x1 - 1, y2, c) - sum(x2, y1 - 1, c) + sum(x1 - 1, y1 - 1 , c);
}

void add(int x, int y, int c)
{
	for(int i = x; i < N_MAX; i += LOWBIT(i))
		for(int j = y; j < N_MAX; j += LOWBIT(j))
			tree[i][j][c] ++;
}

void change(int x, int y, int c)
{
	int org = matrix[x][y];
	matrix[x][y] = c;
	for(int i = x; i < N_MAX; i += LOWBIT(i))
		for(int j = y; j < N_MAX; j += LOWBIT(j))
			tree[i][j][org] --, tree[i][j][c] ++;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, m, q;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			scanf("%d", &matrix[i][j]);
			add(i, j, matrix[i][j]);
		}
	scanf("%d", &q);
	while(q --)
	{
		int cmd;
		scanf("%d", &cmd);
		if(cmd == 1)
		{
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			change(x, y, c);
		}
		else
		{
			int x1, y1, x2, y2, c;
			scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
			printf("%d\n", ask(x1, y1, x2, y2, c));
		}
	}
}
