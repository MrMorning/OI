#include <cstdio>
#include <cmath>
#include <algorithm>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SQR(x) ((x) * (x))

const int N_BALL_MAX = 1501;
const double INF = 10E100;

struct Ball
{
	double x, y;
	int need;
	bool operator< (const Ball &another) const
	{
		return x < another.x;
	}
};

double dist(Ball &a, Ball &b)
{
	return sqrt(SQR(a.x - b.x) + SQR(a.y - b.y));
}

Ball ball[N_BALL_MAX];
int n;
double f[N_BALL_MAX][4];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%lf%lf%d", &ball[i].x, &ball[i].y, &ball[i].need);
		for(int j = 0; j <= 3; j ++)
			f[i][j] = INF;
	}
	ball[0].x = 0, ball[0].y = 0;
	std::sort(ball + 1, ball + 1 + n);
	f[0][3] = 0;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j <= 3; j ++)
		{
			int cur_need = ball[i + 1].need;
			double cost = 0;

			//move directly to the next ball
			cost = dist(ball[i + 1], ball[i]);
			cur_need -= j;
			int left;
			if(cur_need > 0)
			{
				int more = (cur_need - 1) / 3 + 1;
				left = more * 3 - cur_need;
				cost += 2 * more * ball[i + 1].y;
			}
			f[i + 1][left] = MIN(f[i + 1][left], f[i][j] + cost);
			//first move to the river, then to the next ball
			cur_need = ball[i + 1].need;
			cost = sqrt(SQR(ball[i].y + ball[i + 1].y) + SQR(ball[i + 1].x - ball[i].x));
			cur_need -= 3;
			if(cur_need > 0)
			{
				int more = (cur_need - 1) / 3 + 1;
				left = more * 3 - cur_need;
				cost += 2 * more * ball[i + 1].y;
			}
			f[i + 1][left] = MIN(f[i + 1][left], f[i][j] + cost);
		}
	printf("%.2lf", MIN(f[n][0], MIN(f[n][1], f[n][2])));
}
