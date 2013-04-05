#include <cstdio>
#define IDX(x,y) (x * n + y + 1)
int nextOdd()
{
	static int x = 101;
	int tmp = x;
	x += 2;
	return tmp;
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	printf("%d", n);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(i + j > n)
				printf(" %d", IDX(i,j));
	printf("\n");
	printf("%d", nextOdd());
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(i + j == n)
				printf(" %d", IDX(i,j));
	printf("\n");
	for(int i = n; i >= 2; i --)
	{
		printf("%d", nextOdd());
		for(int j = 0; j < i; j ++)
			printf(" %d", IDX(j, i - j - 1));
		printf("\n");
	}
}
