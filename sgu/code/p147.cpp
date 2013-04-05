#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;
const int oo = 0x3f3f3f3f;

struct Line
{
	int k, b;
	Line(int _k, int _x, int _y):
		k(_k)
	{
		b = _y - _k * _x;
	}
	int fx(int _x)
	{
		return k * _x + b;
	}

	int fy(int _y)
	{
		return (_y - b) / k;
	}
};

int n, x[4], y[4];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= 3; i ++)
		scanf("%d%d", &x[i], &y[i]);
	if(y[1] < y[2])
		swap(y[1], y[2]), swap(x[1], x[2]);
	if(x[2] < x[1])
		for(int i = 1; i <= 3; i ++)
		{
			int tmp = x[i];
			x[i] = y[i];
			y[i] = n - tmp;
		}
	if(y[1] < y[2])
		swap(y[1], y[2]), swap(x[1], x[2]);

	assert(y[1] >= y[2] && x[1] <= x[2]);
	int ans = oo;
	int req = max(abs(x[2] - x[1]), abs(y[2] - y[1])) / 2;
	int dx = abs(x[1] - x[2]), dy = abs(y[1] - y[2]);
	if(dy >= dx)
	{
		Line l1(1, x[1], y[1]), l2(-1, x[2], y[2]),
			 l3(-1, x[1], y[1]), l4(1, x[2], y[2]);
		for(int i = y[1] - 1; i >= y[2] + 1; i --)
		{
			int lb = max(l1.fy(i), l2.fy(i)),
				rb = min(l3.fy(i), l4.fy(i));
			lb = min(lb, n); rb = max(rb, 1);
			int d = min(abs(i - y[1]), abs(y[2] - i));
			if(d >= req)
				continue;
			if(y[3] + d == i || y[3] - d == i)
			{
				if(x[3] - d <= rb && x[3] + d >= lb)
					ans = min(ans, d);
			}
			else if(y[3] - d < i && i < y[3] + d)
			{
				if((lb <= x[3] - d && x[3] - d <= rb) || (lb <= x[3] + d && x[3] + d <= rb))
					ans = min(ans, d);
			}
		}
	}
	else
	{
		Line l1(1, x[1], y[1]), l2(-1, x[2], y[2]),
			 l3(-1, x[1], y[1]), l4(1, x[2], y[2]);
		for(int i = x[1] + 1; i <= x[2] - 1; i ++)
		{
			int rb = min(l1.fx(i), l2.fx(i)),
				lb = max(l3.fx(i), l4.fx(i));
			lb = min(lb, n); rb = max(rb, 1);
			int d = min(abs(i - x[1]), abs(i - x[2]));
			if(d >= req)
				continue;
			if(x[3] + d == i || x[3] - d == i)
			{
				if(y[3] - d <= rb && y[3] + d >= lb)
					ans = min(ans, d);
			}
			else if(x[3] - d < i && i < x[3] + d)
			{
				if((lb <= y[3] - d && y[3] - d <= rb) || (lb <= y[3] + d && y[3] + d <= rb))
					ans = min(ans, d);
			}
		}
	}

	if(ans == oo)
		printf("NO\n%d\n", max(abs(x[2] - x[1]), abs(y[2] - y[1])) - 1);
	else
		printf("YES\n%d\n", ans);
}
