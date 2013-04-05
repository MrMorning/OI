#include <cstdio>
#include <cstdlib>

int main()
{
	srand(42);
	freopen("t.in", "w", stdout);
	printf("100 99\n");
	printf("1 1 ");
	for(int i = 0; i < 99; i ++)
	{
		int t = rand() % 20000 + 1;
		printf("0 20000 ");//, t, t + rand() % 10);
	}
	printf("\n");
	for(int i = 0; i < 99; i ++)
		printf("1 1 -1000 %d %d\n", i + 1, i + 2);
}
