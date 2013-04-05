#include <cstdio>
#define INLINE __attribute__((always_inline))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef long long crdnt_t;
#define CRDNT_FMT "%lld"
const int N_MAX = 1000001;
int n, c[3], sum[N_MAX];
crdnt_t f[N_MAX];
struct Point
{
	crdnt_t x, y;
	Point(crdnt_t _x = 0, crdnt_t _y = 0): x(_x), y(_y){};
};
crdnt_t fx(int j) INLINE;
crdnt_t fy(int j) INLINE;
crdnt_t fa(int i) INLINE;
crdnt_t calc_p(Point &p, int i) INLINE;
crdnt_t fx(int j)
{
	return sum[j];
}
crdnt_t fy(int j)
{
	return f[j] + (crdnt_t)c[0] * sum[j] * sum[j] - (crdnt_t)c[1] * sum[j];
}
crdnt_t fa(int i)
{
	return (crdnt_t)2 * c[0] * sum[i];
}
crdnt_t calc_p(Point &p, int i)
{
	return p.y - (crdnt_t)p.x * fa(i);
}
void init()
{
	scanf("%d", &n);
	scanf("%d%d%d", &c[0], &c[1], &c[2]);
	for(int i = 1, w; i <= n; i ++)
	{
		scanf("%d", &w);
		sum[i] = sum[i - 1] + w;
	}
}
void work()
{
	static Point stack[N_MAX];
	int top = 0;
	stack[top ++] = Point(0, 0);
	int ptr = 0;
	for(int i = 1; i <= n; i ++)
	{
		while(ptr < top - 1 && calc_p(stack[ptr], i) < calc_p(stack[ptr + 1], i))
			ptr ++;
		f[i] = calc_p(stack[ptr], i) + (crdnt_t)c[0] * sum[i] * sum[i] + (crdnt_t)c[1] * sum[i] + c[2];
		Point new_pnt = Point(fx(i), fy(i));
		while(top >= 1)
		{
			Point p1 = stack[top - 2],
				  p2 = stack[top - 1];
			if((crdnt_t)(p1.y - p2.y) * (p2.x - new_pnt.x) < (p2.y - new_pnt.y) * (p1.x - p2.x))
				top --, ptr = MIN(ptr, top - 1);
			else
				break;
		}
		stack[top ++] = new_pnt;
	}
	printf(CRDNT_FMT "\n", f[n]);
}
int main()
{
	freopen("t.in", "r", stdin);
	init();
	work();
	//bruce();
}
