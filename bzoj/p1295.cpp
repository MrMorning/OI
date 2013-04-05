#include <cstdio>
#include <cstring>
#include <cmath>
#include <deque>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int N_MAX = 30;
const int OFFSET[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct Point
{
	int x, y, step;
	Point(int _x = -1, int _y = -1, int _step = -1):
		x(_x), y(_y), step(_step){}
};

bool obs[N_MAX][N_MAX];
int n, m;

double inline dist(const Point &a, const Point &b)
{
#define SQR(x) ((x)*(x))
	return sqrt(SQR(a.x - b.x) + SQR(a.y - b.y));
#undef SQR
}
double bfs(const Point &begin, int max_step)
{
	using namespace std;
	deque<Point> DQ;
	static bool vis[N_MAX][N_MAX];

	memset(vis, 0, sizeof(vis));

	DQ.push_back(begin);
	vis[begin.x][begin.y] = true;

	double ret = 0;
	while(! DQ.empty())
	{
		Point u = DQ.front(); DQ.pop_front();
		if(u.step > max_step)
			return ret;
		ret = MAX(ret, dist(begin, u));
		for(int dir = 0; dir < 4; dir ++)
		{
			int x_new = u.x + OFFSET[dir][0],
				y_new = u.y + OFFSET[dir][1];
			if(! (0 <= x_new && x_new < n && 0 <= y_new && y_new < m))
				continue;
			if(vis[x_new][y_new])
				continue;
			vis[x_new][y_new] = true;
			Point v = Point(x_new, y_new, 0);
			if(obs[x_new][y_new])
			{
				v.step = 1;
				DQ.push_back(v);
			}
			else
				DQ.push_front(v);
		}
	}
	return ret;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int t;
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 0; i < n; i ++)
	{
		static char str[N_MAX];
		scanf("%s", str);
		for(int j = 0; j < m; j ++)
			obs[i][j] = str[j] - '0';
	}
	double ans = 0;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			ans = MAX(ans, bfs(Point(i, j, obs[i][j]), t));
	printf("%.6lf\n", ans);
}
