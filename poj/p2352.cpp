#include <cstdio>
#define MAX_RANGE 32005
#define MAXN 15005
int C[MAX_RANGE], n;
int ans[MAXN];

int lowbit(int x)
{return x & (-x);}

void Add(int i, int x)
{
	while(i <= MAX_RANGE)
	{
		C[i] += x;
		i += lowbit(i);
	}
}
int Sum(int i)
{
	int cnt = 0;
	while(i > 0)
		cnt += C[i], i -= lowbit(i);
	return cnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1, x, y; i <= n; i ++)
	{
		scanf("%d %d\n", &x, &y);
		ans[Sum(x + 1)] ++;
		Add(x + 1, 1);
	}
	for(int i = 0; i < n; i ++)
		printf("%d\n", ans[i]);
}
