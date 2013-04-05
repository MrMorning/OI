#include <cstdio>
#include <cstdlib>
int seed;
int x[1000], y, n, m;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	int y = rand() % 20 + 1;
	int left = y;
	for(int i = 0; i < n - 1; i ++)
	{
		x[i] = (left ? rand() % left + 1 : 0);
		left -= x[i];
	}
	printf("%d %d %d\n", n, m, y);
	for(int i = 0; i < n - 1; i ++)
		printf("%d ", x[i]);
	printf("%d\n", left);
}
