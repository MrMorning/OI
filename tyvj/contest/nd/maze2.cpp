#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct State
{
	int x, y, idx;
	State(){}
	State(int _x, int _y, int _idx):
		x(_x), y(_y), idx(_idx){}
} Q[1000000];

struct Point
{
	int x, y;
} p[1000000];
int vis[1000][1000];
int r, c;

bool check(int lim)
{
	int qt = 0;
	int t = vis[0][0];
	if(p[t].x + p[t].y < lim)
		return false;
	Q[qt ++] = State(0, 0, 0);
	for(int i = 0; i < qt; i ++)
	{
		State u = Q[i];
		if(u.x == r - 1 && u.y == c - 1)
			return true;
		for(int d = 0; d < 4; d ++)
		{
			int nx = offset[d][0] + u.x,
				ny = offset[d][1] + u.y;
			if(0 <= nx && nx < r)
				if(0 <= ny && ny < c)
				{
					t = vis[nx][ny];
					if(abs(p[t].x - nx) + abs(p[t].y - ny) < lim)
						continue;
					Q[qt ++] = State(nx, ny, 0);
				}
		}
	}
	return false;
}
int main()
{
	freopen("maze2.in", "r", stdin);
	freopen("maze2.out", "w", stdout);
	memset(vis, -1, sizeof(vis));
	int n;
	scanf("%d%d%d", &r, &c, &n);
	int qt = 0;
	for(int i = 0; i < n; i ++)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].x --, p[i].y --;
		if(vis[p[i].x][p[i].y] == -1)
		{
			Q[qt ++] = State(p[i].x, p[i].y, i);
			vis[p[i].x][p[i].y] = i;
		}
	}

	for(int i = 0; i < qt; i ++)
	{
		State u = Q[i];
		for(int d = 0; d < 4; d ++)
		{
			int nx = offset[d][0] + u.x,
				ny = offset[d][1] + u.y;
			if(0 <= nx && nx < r)
				if(0 <= ny && ny < c)
					if(vis[nx][ny] == -1)
					{
						vis[nx][ny] = u.idx;
						Q[qt ++] = State(nx, ny, u.idx);
					}
		}
	}
	int lb = 0, rb = max(r, c);
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(check(mid))
			lb = mid;
		else
			rb = mid;
	printf("%d\n", lb);
}
