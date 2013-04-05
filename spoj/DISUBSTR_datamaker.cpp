#include <cstdio>
#include <cstdlib>
int seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	printf("1\n");
	for(int t = 0; t < 1; t ++, printf("\n"))
		for(int i = 0; i < 1000; i ++)
			printf("%c", rand() % (5) + 33);
}
