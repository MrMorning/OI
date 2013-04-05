#include <cstdio>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

namespace Solve
{
	const int MAXN = 100001;
	typedef double Val_t;
	struct Point
	{
		int x, y;
		Point(){};
		Point(int _x, int _y): x(_x), y(_y){};
	};
	Val_t getSlope(int, int);
	Point point[MAXN];
	int queue[MAXN];
	int tail = 0;
	void solve();
	void debug();
}

Solve::Val_t Solve::getSlope(int a, int b)
{
	return (Val_t)(point[a].y - point[b].y) / (point[a].x - point[b].x);
}

void Solve::debug()
{
	for(int i = 0; i < tail - 1; i ++)
		if(getSlope(queue[i], queue[i + 1]) > getSlope(queue[i + 1], queue[i + 2]))
			printf("haha");
}

void Solve::solve()
{
	int n, k;
	scanf("%d%d", &n, &k);
	point[0] = Point(0, 0);
	int sum = 0;
	for(int i = 0, tmp; i < n; i ++)
	{
		scanf("%d", &tmp);
		sum += tmp;
		point[i + 1] = Point(i + 1, sum);
	}
	Val_t ans = 0;
	for(int i = k, j = 0; i <= n; i ++)
	{
		while(tail >= 2 && getSlope(queue[tail - 1], i - k) < getSlope(queue[tail - 2], i - k))
			tail --, j = MIN(j, tail - 1);
		queue[tail ++] = i - k;
		while(j <= tail - 2 && getSlope(queue[j], i) < getSlope(queue[j + 1], i))
			j ++;
		ans = MAX(ans, getSlope(queue[j], i));
	}
	printf("%.0lf\n", ans * 1000);
}

int main()
{
#ifndef STDIO
	freopen("t.in", "r", stdin);
#endif
	Solve::solve();
}
