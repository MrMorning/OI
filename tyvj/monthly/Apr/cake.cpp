#include <cstdio>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const int N_MAX = 1501;
int map[N_MAX][N_MAX], n, m;
int step[N_MAX][N_MAX];
int src_x, src_y;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	for(int x = n; x >= 1; x --)
	{
		for(int y = 1; y <= m; y ++)
		{
			map[x][y] = getchar() - '1';
		}
		getchar();
	}
	scanf("%d %d\n", &src_x, &src_y);
	int pre_x = src_x, pre_y = src_y;
	int now_x, now_y;
	while(1)
	{
		int dir = map[pre_x][pre_y];
		now_x = pre_x + dx[dir];
		now_y = pre_y + dy[dir];
		if(! (1 <= now_x && now_x <= n && 1 <= now_y && now_y <= m))
		{
			printf("%d %d\n", pre_x, pre_y);
			return 0;
		}
		if(step[now_x][now_y])
		{
			int len = step[pre_x][pre_y] - step[now_x][now_y] + 1;
			if(len == 2)
				printf("%d %d %d %d\n", MIN(pre_x, now_x), MIN(pre_y, now_y), MAX(pre_x, now_x), MAX(pre_y, now_y));
			else
				printf("%d\n", len);
			return 0;
		}
		step[now_x][now_y] = step[pre_x][pre_y] + 1;
		pre_x = now_x, pre_y = now_y;
	}
}
