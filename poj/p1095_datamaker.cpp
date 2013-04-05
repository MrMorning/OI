#include <cstdio>
#include <cstdlib>
int main()
{
	freopen("t.in", "w", stdout);
	int seed;
	scanf("%d", &seed);
	srand(seed);
	for(int i = 1; i <= 10; i ++)
		printf("%d\n", rand() % 50000000 + 1);
	printf("0\n");
}
