#include <cstdio>
#define MAXN 1030

int tree[MAXN][MAXN];
int n;

int lowbit(int x)
{return x & (- x);}

void Add(int x, int y, int v)
{
	for(int i = x; i <= MAXN; i += lowbit(i))
		for(int j = y; j <= MAXN; j +=lowbit(j))
			tree[i][j] += v;
}

int Sum(int x, int y)
{
	int cnt = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		for(int j = y; j > 0; j -=lowbit(j))
			cnt += tree[i][j];
	return cnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("0 %d\n", &n);
	while(1)
	{
		int ctrl;
		scanf("%d", &ctrl);
		if(ctrl == 1)
		{
			int x, y, a;
			scanf("%d %d %d\n", &x, &y, &a);
			x ++, y ++;
			Add(x, y, a);
		}
		else if(ctrl == 2)
		{
			int x1, y1, x2, y2;
			scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
			x1 ++, x2 ++, y1 ++, y2 ++;
			printf("%d\n", Sum(x2, y2) - Sum(x2, y1 - 1) - Sum(x1 - 1, y2) + Sum(x1 - 1, y1 - 1));
		}
		else break;
	}
}
