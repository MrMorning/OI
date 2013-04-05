#include <cstdio>
#include <cstring>
const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
char board[15][15];
char str[15];
int n, m;
int main()
{
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int res = 0;
	for(int i = 0; i < n; i ++)
	{
		scanf("%s", str);
		for(int j = 0; j < (int)strlen(str); j ++)
			board[i][j] = str[j];
	}

	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			if(board[i][j] == 'W')
			{
				for(int d = 0; d < 4; d ++)
				{
					int nx = i + offset[d][0],
						ny = j + offset[d][1];
					if(0 <= nx && nx < n)
						if(0 <= ny && ny < m)
							if(board[nx][ny] == 'P')
							{
								res ++;
								break;
							}
				}
			}
	printf("%d\n", res);
}
