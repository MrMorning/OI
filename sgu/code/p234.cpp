#include <cstdio>
#include <cstring>
#include <cassert>
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
int r, c;
int ctime = 0;
int match[210][210];
int vis[210][210];
bool marked[210][210];
bool matched[210][210];
int fine[210][210];

bool aug(int x, int y)
{
	for(int o = 0; o < 4; o ++)
	{
		int x2 = x + dx[o], y2 = y + dy[o];
		if(0 <= x2 && x2 < r)
			if(0 <= y2 && y2 < c)
				if(fine[x2][y2] && vis[x2][y2] != ctime)
				{
					vis[x2][y2] = ctime;
					if(match[x2][y2] == -1 || aug(match[x2][y2] / c, match[x2][y2] % c))
					{
						match[x2][y2] = x * c + y;
						return true;
					}
				}
	}
	return false;
}

void dfs(int x, int y)
{
	marked[x][y] = true;
	for(int o = 0; o < 4; o ++)
	{
		int x2 = x + dx[o], y2 = y + dy[o];
		if(0 <= x2 && x2 < r)
			if(0 <= y2 && y2 < c)
				if(fine[x2][y2])
					if(!marked[x2][y2])
					{
						marked[x2][y2] = true;
						assert(match[x2][y2] != -1);
						dfs(match[x2][y2] / c, match[x2][y2] % c);
					}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &r, &c);
	int ans = 0;
	for(int i = 0; i < r; i ++)
		for(int j = 0; j < c; j ++)
		{
			scanf("%d", &fine[i][j]);
			ans += fine[i][j];
		}
	memset(match, -1, sizeof(match));
	for(int i = 0; i < r; i ++)
		for(int j = 0; j < c; j ++)
			if((i + j) & 1 && fine[i][j])
			{
				ctime ++;
				if(aug(i, j))
					matched[i][j] = true, ans --;
			}
	printf("%d\n", ans);
	memset(marked, 0, sizeof(marked));
	for(int i = 0; i < r; i ++)
		for(int j = 0; j < c; j ++)
			if((i +j) & 1 && fine[i][j] && !matched[i][j])
				if(!marked[i][j])
					dfs(i, j);
	for(int i = 0; i < r; i ++, printf("\n"))
		for(int j = 0; j < c; j ++)
			if(!fine[i][j])
				printf("#");
			else if(((i + j) & 1 && marked[i][j]) || (!((i + j) & 1) && !marked[i][j]))
				printf("G");
			else
				printf(".");
}
