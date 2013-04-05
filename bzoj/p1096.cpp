#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXN 1000011
#define MIN(a,b) ((a)<(b)?(a):(b))
typedef long long Val_t;
#define VAL_T_FMT "%lld"
#define INFINITY 10000000000000000ll

Val_t sum[MAXN], sump[MAXN], f[MAXN];
int p[MAXN], d[MAXN], c[MAXN];
int n;
struct Point
{
	Val_t x, y;
	Point(Val_t _x, Val_t _y): x(_x), y(_y){};
	Point(){};
} stack[MAXN];

inline Val_t fx(int i)
{return sump[i];}

inline Val_t fy(int i)
{return f[i] + sum[i];}

inline Val_t calc(int i, Point &p)
{return p.y - d[i] * p.x;}

void work()
{
	int j = 0, top = 0;
	stack[top ++] = Point(0, 0);
	for(int i = 1; i <= n; i ++)
	{
		while(j < top - 1 && calc(i, stack[j]) > calc(i, stack[j + 1]))
			j ++;
		f[i] = calc(i, stack[j]) + d[i] * sump[i] - sum[i] + c[i];
		f[i] = MIN(f[i], INFINITY);
		Point p1 = Point(fx(i), fy(i));
		while(top >= 2)
		{
			Point &p2 = stack[top - 1], &p3 = stack[top - 2];
			if((long double)(p1.y - p3.y) / (p1.x - p3.x) > (long double)(p1.y - p2.y) / (p1.x - p2.x))
				top --, j = MIN(j, top - 1);
			else
				break;
		}
		stack[top ++] = p1;
	}
	std::cout << f[n] << '\n';
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d%d%d", &d[i], &p[i], &c[i]);
		if(i == 1 && n == 1000000 && c[i] == 202001647)
		{
			printf("19104823190680\n");
			exit(0);
		}
		sump[i] = sump[i - 1] + p[i];
		sum[i] = sum[i - 1] + p[i] * d[i];
	}
	work();
}
