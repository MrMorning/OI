#include <cstdio>
#include <cstdlib>
#include <cstring>
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
int val[100][100];
bool vis[100][100];
int main()
{
	freopen("t.in", "w", stdout);
	srand(-1);
	printf("30\n");
	for(int rep = 0; rep < 30; rep ++)
	{
		memset(vis, 0, sizeof(vis));
		memset(val, 0, sizeof(val));
		int n = rand() % 90 + 10, m = rand() % 90 + 10;
		printf("%d %d\n", n, m);
		int k = rand() % 30 + 1;
		int cnt = n * m * k / 100;
		while(cnt --)
		{
			int x, y;
			while(1)
			{
				x = rand() % n, y = rand() % m;
				if(!vis[x][y])
					break;
			}
			vis[x][y] = true;
			val[x][y] = rand() % 50 + 1;
			for(int d = 0; d < 4; d ++)
			{
				int nx = x + dx[d],
					ny = y + dy[d];
				if(0 <= nx && nx < n)
					if(0 <= ny && ny < m)
						vis[nx][ny] = true;
			}
	
		}
		for(int i = 0; i < n; i ++, printf("\n"))
			for(int j = 0; j < m; j ++)
				printf("%d ", val[i][j]);
	}
}
