#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define RANGE 1000000000
using std::swap;
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	printf("%d %d\n", n, m);
	srand(seed);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % RANGE + 1);
	printf("\n");
	for(int i = 1; i <= m; i ++)
	{
		int c = rand() % 2;
		if(c)
		{
			int l = rand() % n + 1;
			int r = rand() % (n - 1) + 1;
			if(l > r) std::swap(l, r);
			if(l == r) r ++;
			printf("Q %d %d %d\n", l, r, rand() % (r - l + 1) + 1);
		}
		else
			printf("C %d %d\n", rand() % n + 1, rand() % RANGE + 1);
	}
}
