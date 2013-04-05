#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
typedef long long Val_t;
#define VAL_T_FMT "%lld"
const int MAXN = 1010;
Val_t sum[MAXN], preCnt[MAXN];
Val_t f1[MAXN], f2[MAXN];
struct Point
{
	Val_t x, y;
	Point(){};
	Point(Val_t _x, Val_t _y): x(_x), y(_y){};
} stack[MAXN];

inline Val_t fx(int i)
{return sum[i];}

inline Val_t fy(int i)
{return f1[i] - preCnt[i] + sum[i] * sum[i];}

inline Val_t calc(int i, Point &p)
{return p.y - sum[i] * p.x;}

void solve(int n, int m)
{
	memset(f1, 0x3f, sizeof(Val_t) * (n + 1));
	stack[0] = Point(0, 0);
	f1[0] = 0;
	int top = 1;
	for(int j = 1; j <= m; j ++)
	{
		int p = 0;
		memset(f2, 0x3f, sizeof(f2));
		for(int i = 1; i <= n; i ++)
		{
			while(p < top - 1 && calc(i, stack[p + 1]) < calc(i, stack[p]))
				p ++;
			f2[i] = calc(i, stack[p]) + preCnt[i];
			Point p1 = Point(fx(i), fy(i));
			while(top >= 2)
			{
				Point &p2 = stack[top - 1], &p3 = stack[top - 2];
				if((double)(p1.y - p2.y) / (p1.x - p2.x) < (double)(p1.y - p3.y) / (p1.x - p3.x))
					top --, p = MIN(p, top - 1);
				else
					break;
			}
			stack[top ++] = p1;
		}
		memcpy(f1, f2, sizeof(Val_t) * (n + 1));
		top = 0;
	}
	printf(VAL_T_FMT "\n", f2[n]);
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if(n == 0)
			break;
		for(int i = 1, t; i <= n; i ++)
		{
			scanf("%d", &t);
			sum[i] = sum[i - 1] + t;
			preCnt[i] = preCnt[i - 1] + t * sum[i - 1];
		}
		solve(n, m + 1);
	}
}
