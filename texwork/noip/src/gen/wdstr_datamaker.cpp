#include <cstdio>
#include <cstdlib>
int t, n, r, seed;
int main()
{
	scanf("%d%d%d%d", &t, &n, &r, &seed);
	printf("%d\n", t);
	srand(seed);
	while(t --)
	{
		for(int i = 0; i < n; i ++)
			printf("%c", rand() % r + 'a');
		printf("\n");
	}
}
