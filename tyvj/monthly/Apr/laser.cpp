#include <cstdio>
const int N_MAX = 1501, N_QUEUE_MAX = N_MAX * N_MAX * 3; 
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

#define IS_WALL(x, y) (map[x][y] == 'x')
#define IS_SOURCE(x, y) (map[x][y] == 'j')
#define IS_TARGET(x, y) (map[x][y] == 'y')
#define IS_EMPTY(x, y) (map[x][y] == 'o')

struct State
{
	int x, y, dir, step;
	State(){};
	State(int _x, int _y, int _dir, int _step): x(_x), y(_y), dir(_dir), step(_step) {};
} queue[N_QUEUE_MAX];
int head, tail;
char map[N_MAX][N_MAX];
bool vis[N_MAX][N_MAX][4];
int n, m;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &m, &n);
	for(int i = 1; i <= m; i ++)
	{
		for(int j = 1; j <= n; j ++)
			map[i][j] = getchar();
		getchar();
	}
	for(int i = 1; i <= m; i ++)
		map[i][0] = map[i][n + 1] = 'x';
	for(int j = 1; j <= n; j ++)
		map[0][j] = map[m + 1][j] = 'x';
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j <= n; j ++)
			if(IS_SOURCE(i, j))
			{
				for(int dir = 0; dir < 4; dir ++)
				{
					queue[tail ++] = State(i, j, dir, 0);
					vis[i][j][dir] = true;
				}
				for(; head != tail; head = (head + 1) % N_QUEUE_MAX)
				{
					State s = queue[head];
					for(int dir = 0; dir < 4; dir ++)
					{
						int now_x = s.x, now_y = s.y;
						while(IS_EMPTY(now_x + dx[dir], now_y + dy[dir]) && ! vis[now_x + dx[dir]][now_y + dy[dir]][dir])
						{
							now_x += dx[dir], now_y += dy[dir];
							vis[now_x][now_y][dir] = true;
							if(! vis[now_x][now_y][(dir + 1) % 4])
							{
								queue[tail] = State(now_x, now_y, (dir + 1) % 4, s.step + 1);
								tail = (tail + 1) % N_QUEUE_MAX;
								vis[now_x][now_y][(dir + 1) % 4] = true;
							}
							if(! vis[now_x][now_y][(dir + 3) % 4])
							{
								queue[tail] = State(now_x, now_y, (dir + 3) % 4, s.step + 1);
								tail = (tail + 1) % N_QUEUE_MAX;
								vis[now_x][now_y][(dir + 3) % 4] = true;
							}
						}
						if(IS_TARGET(now_x + dx[dir], now_y + dy[dir]))
						{
							printf("%d\n", s.step);
							return 0;
						}
						else if(vis[now_x + dx[dir]][now_y + dy[dir]][dir])
							continue;
					}
				}
				return 0;
			}
}
