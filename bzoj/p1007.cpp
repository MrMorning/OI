#include <cstdio>
#include <algorithm>
const int N_LINE_MAX = 50010;
struct Line
{
	int a, b;
	int idx;
} line[N_LINE_MAX], stack[N_LINE_MAX];

bool cmp_by_k(const Line &l1, const Line &l2)
{
	if(l1.a < l2.a)
		return 1;
	else if(l1.a > l2.a)
		return 0;
	else
		return l1.b > l2.b;
}

bool cmp_by_idx(const Line &l1, const Line &l2)
{
	return l1.idx < l2.idx;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d%d", &line[i].a, &line[i].b);
		line[i].idx = i;
	}
	std::sort(line + 1, line + 1 + n, cmp_by_k);
	int top = 0;
	stack[top ++] = line[1];
	stack[top ++] = line[2];
	for(int i = 3; i <= n; i ++)
	{
		bool failed = false;
		while(1)
		{
			if(top < 2)
				break;
			Line &l1 = stack[top - 2],
				 &l2 = stack[top - 1],
				 &l3 = line[i];
			static int a[4], b[4];
			a[1] = l1.a, a[2] = l2.a, a[3] = l3.a;
			b[1] = l1.b, b[2] = l2.b, b[3] = l3.b;
			if(a[3] == a[2])
			{
				failed = true;
				break;
			}
			if((double)(b[2] - b[3]) / (a[3] - a[2]) <= (double)(b[1] - b[2]) / (a[2] - a[1]))
				top --;
			else
				break;
		}
		if(failed)
			continue;
		stack[top ++] = line[i];
	}
	std::sort(stack, stack + top, cmp_by_idx);
	for(int i = 0; i < top; i ++)
		printf("%d ", stack[i].idx);

}
