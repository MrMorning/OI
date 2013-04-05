#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAXN 200000
#define MAX_VAL 200000

using std::cout;

struct Cow
{
	int v, x;
} cow[MAXN];
int n;
long long ans;
long long tree[2][MAXN];
long long total[MAXN];

inline int lowbit(int i)
{return i & (- i);}

inline int max(int a, int b)
{return a>b?a:b;}

void Add(int t, int i, int c)
{
	while(i > 0)
		tree[t][i] += c, i -= lowbit(i);
}

long long Sum(int t, int i)
{
	long long cnt = 0;
	while(i <= MAX_VAL)
		cnt += tree[t][i], i += lowbit(i);
	return cnt;
}

int comp(const void *a, const void *b)
{return ((Cow*)a)->v - ((Cow*)b)->v;}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d %d\n", &cow[i].v, &cow[i].x);
	qsort(cow + 1, n, sizeof(Cow), comp);
	for(int i = 1; i <= n; i ++)
		total[i] = total[i-1] + cow[i].x;
	for(int i = 1; i <= n; i ++)
	{
		Add(0, cow[i].x, 1), Add(1, cow[i].x, cow[i].x);
		long long count = i - Sum(0, cow[i].x);//count为i之前横坐标严格小于cow[i].x的个数
		long long tmp = total[i] - Sum(1, cow[i].x);//...............................的横坐标和
		ans += cow[i].v * (cow[i].x * count - tmp  + total[i] - tmp - cow[i].x * (i - count));
	}
	cout << ans;

}
