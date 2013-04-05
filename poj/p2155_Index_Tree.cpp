#include <cstdio>
#include <cstring>
#define MAXN 1010
int C[MAXN][MAXN];

inline int lowbit(int x)
{return x &(- x);}

void Add(int x, int y, int v)
{
	for(int i = x; i <= MAXN; i += lowbit(i))
		for(int j = y; j <= MAXN; j += lowbit(j))
			C[i][j] += v;
}

int Sum(int x,int y)
{
	int cnt = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		for(int j = y; j > 0; j -= lowbit(j))
			cnt += C[i][j];
	return cnt;
}

int main()
{
	freopen("t.in", "r", stdin);
	int test_num, n, m;
	scanf("%d", &test_num);
	while(test_num --)
	{
		memset(C, 0, sizeof(C));
		scanf("\n%d %d", &n, &m);
		while(m --)
		{
			char ctrl;
			int x1, x2, y1, y2;
			scanf("\n%c %d %d", &ctrl, &x1, &y1);
			if(ctrl == 'C')
			{
				scanf("%d %d", &x2, &y2);
				Add(x1, y1, 1);
				Add(x1, y2 + 1, 1);
				Add(x2 + 1, y1, 1);
				Add(x2 + 1, y2 + 1, 1);
			}
			else
				printf("%d\n", Sum(x1, y1) % 2);
		}
		scanf("\n");
		printf("\n");
	}
}
