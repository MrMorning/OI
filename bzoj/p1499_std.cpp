#include <stdio.h>

const int dx[] = {0,0,0,-1,1}, dy[] = {0,-1,1,0,0};
char a[200][201];
int s[200][200], m, n, res;
struct {int bgn, end, d; } b[200];
struct node{int pos, key; } q[200];

void F(int x, int y, int d, int max_pos)
{
	int front = 0, back = 0, j = 0;
	while (0 <= x && x < m && 0 <= y && y < n)
	{
		if (a[y][x] == 'x')
			front = 0, back = 0;
		else
		{
			while (front < back && q[back-1].key <= s[y][x]-j) --back;
			q[back++] = (node){j, s[y][x]-j};
			if (max_pos < j-q[front].pos) ++front;
			s[y][x] = q[front].key+j;
			if (s[y][x] > res) res = s[y][x];
		}
		x += dx[d]; y += dy[d]; ++j;
	}
}

int main()
{
	int x, y, k;
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d%d%d%d\n", &n, &m, &y, &x, &k);
	for (int i = 0; i < n; ++i)
	{
		gets(a[i]);
		for (int j = 0; j < m; ++j)
			s[i][j] = -10000;
	}
	for (int i = 0; i < k; ++i)
		scanf("%d%d%d", &b[i].bgn, &b[i].end, &b[i].d);
	s[y-1][x-1] = 0;
	for (int i = 0; i < k; ++i)
	{
		int t = b[i].end-b[i].bgn+1;
		switch (b[i].d)
		{
			case 1: for (int j = 0; j < m; ++j) F(j, n-1, 1, t); break;
			case 2: for (int j = 0; j < m; ++j) F(j, 0, 2, t); break;
			case 3: for (int j = 0; j < n; ++j) F(m-1, j, 3, t); break;
			case 4: for (int j = 0; j < n; ++j) F(0, j, 4, t);
		}
	}
	printf("%d\n", res);
}
