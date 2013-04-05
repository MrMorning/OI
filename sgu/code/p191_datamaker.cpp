#include <cstdio>
#include <cstdlib>
int seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	int n1 = rand() % 30000 + 1, n2 = rand() % 30000 + 1;
	while(n1 --)
		printf("%c", rand() % 2 + 'A');
	printf("\n");
	while(n2 --)
		printf("%c", rand() % 2 + 'A');
}
