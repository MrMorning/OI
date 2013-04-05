#include <cstdio>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))

namespace Solve
{
	const int MAXN = 100001;
	struct Point
	{
		int x, y;
		Point(){};
		Point(int _x, int _y): x(_x), y(_y){};
	};
	double getSlope(int, int);
	Point point[MAXN];
	int queue[MAXN];
	int head = 0, tail = 0;
	void solve();
	void debug();
}

double Solve::getSlope(int a, int b)
{
	return (double)(point[a].y - point[b].y) / (point[a].x - point[b].x);
}

void Solve::debug()
{
	for(int i = head; i < tail - 2; i ++)
		if(getSlope(queue[i], queue[i + 1]) > getSlope(queue[i + 1], queue[i + 2]))
			printf("fail");
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
	for(int i = 0; i < k; i ++)
	{
		while(tail - head >= 2 && getSlope(queue[tail - 1], i) < getSlope(queue[tail - 2], i))
			tail --;
		queue[tail ++] = i;
		debug();
	}
	double ans = 0;
	for(int i = k, j = 0; i <= n; i ++)
	{
		while(j < tail - 1 && queue[j + 1] <= i - k && getSlope(queue[j], i) < getSlope(queue[j + 1], i))
			j ++;
		ans = MAX(ans, getSlope(queue[j], i));
		while(tail - head >= 2 && getSlope(queue[tail - 1], i) < getSlope(queue[tail - 2], i))
			tail --;
		queue[tail ++] = i;
		debug();
	}
	printf("%.2lf\n", ans);
}

int main()
{
#ifndef STDIO
	freopen("t.in", "r", stdin);
#endif
	Solve::solve();
}
