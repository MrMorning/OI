#include <cstdio>
#include <cstring>
const int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
int a[300][300], color[300][300];
int n, m;
int res;
struct State
{
	int x, y, c;
	State(){}
	State(int _x, int _y, int _c):
		x(_x), y(_y), c(_c){}
} Q[90000];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			scanf("%d", &a[i][j]);
	memset(color, -1, sizeof(color));
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			if(a[i][j] && color[i][j] == -1)
			{
				color[i][j] = 0;
				int qt = 0;
				Q[qt ++] = State(i, j, 0);
				int cnt = 0;
				for(int qh = 0; qh < qt; qh ++)
				{
					State u = Q[qh];
					if(u.c == 1)
						cnt ++;
					for(int d = 0; d < 4; d ++)
					{
						int nx = u.x + dx[d],
							ny = u.y + dy[d];
						if(0 <= nx && nx < n)
							if(0 <= ny && ny < m)
								if(color[nx][ny] == -1 && a[nx][ny])
								{
									color[nx][ny] = !u.c;
									Q[qt ++] = State(nx, ny, !u.c);
								}
					}
				}
				if(qt - cnt > cnt)
				{
					for(int i = 0; i < qt; i ++)
						color[Q[i].x][Q[i].y] ^= 1;
					cnt = qt - cnt;
				}
				res += cnt;
			}
	printf("%d\n", res);
	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < m; j ++)
			if(!a[i][j])
				printf("#");
			else if(color[i][j])
				printf("G");
			else
				printf(".");
}
