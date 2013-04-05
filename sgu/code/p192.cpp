#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point
{
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
};

inline Point operator- (const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

inline double cross(const Point &p1, const Point &p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

struct Segment
{
	Point p1, p2;
	int color;
} seg[300];

inline bool intersect(const Segment &l1, const Segment &l2)
{
	const Point &p1 = l1.p1, &p2 = l1.p2,
		  &q1 = l2.p1, &q2 = l2.p2;
	if(cross(q1 - p1, p2 - p1) * cross(p2 - p1, q2 - p1) > 0)
		if(cross(p1 - q1, q2 - q1) * cross(q2 - q1, p2 - q1) > 0)
			return true;
	return false;
}

double discX[100000];
int discXCnt, segCnt;
double ans[3];

int convert(char ch)
{
	if(ch == 'R')
		return 0;
	else if(ch == 'G')
		return 1;
	else
		return 2;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	while(n --)
	{
		double x1, y1, x2, y2;
		char str[3];
		scanf("%lf%lf%lf%lf%s", &x1, &y1, &x2, &y2, str);
		if(x1 == x2)
			continue;
		if(x1 > x2)
			swap(x1, x2), swap(y1, y2);
		seg[segCnt].p1 = Point(x1, y1);
		seg[segCnt].p2 = Point(x2, y2);
		seg[segCnt].color = convert(str[0]);
		segCnt ++;
	}

	for(int i = 0; i < segCnt; i ++)
		for(int j = i + 1; j < segCnt; j ++)
			if(intersect(seg[i], seg[j]))
			{
				Point p1 = seg[i].p1, p2 = seg[i].p2;
				double a = p1.y - p2.y,
					   b = p2.x - p1.x,
					   c = -(a * p1.x + b * p1.y);
				p1 = seg[j].p1, p2 = seg[j].p2;
				double u = fabs(a * p1.x + b * p1.y + c),
					   v = fabs(a * p2.x + b * p2.y + c);
				double resX = (u * p2.x + v * p1.x) / (u + v);
				discX[discXCnt ++] = resX;
			}
	for(int i = 0; i < segCnt; i ++)
	{
		discX[discXCnt ++] = seg[i].p1.x;
		discX[discXCnt ++] = seg[i].p2.x;
	}

	sort(discX, discX + discXCnt);
	discXCnt = unique(discX, discX + discXCnt) - discX;
	for(int i = 1; i < discXCnt; i ++)
	{
		double midX = (discX[i - 1] + discX[i]) / 2;
		double lowestY = 10e100;
		int lowestC = -1;
		for(int j = 0; j < segCnt; j ++)
		{
			const Point &p1 = seg[j].p1, &p2 = seg[j].p2;
			if(p1.x <= midX && midX <= p2.x)
			{
				double u = fabs(p1.x - midX),
					   v = fabs(p2.x - midX);
				double resY = (u * p2.y + v * p1.y) / (u + v);
				if(resY < lowestY)
				{
					lowestY = resY;
					lowestC = seg[j].color;
				}
			}
		}
		if(lowestC != -1)
			ans[lowestC] += discX[i] - discX[i - 1];
	}
	printf("R %.2lf\n", ans[0]);
	printf("G %.2lf\n", ans[1]);
	printf("B %.2lf\n", ans[2]);
}
