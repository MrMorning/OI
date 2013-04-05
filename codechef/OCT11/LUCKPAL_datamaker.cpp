#include <cstdio>
#include <cstdlib>
int t, n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &t, &n, &seed);
	printf("%d\n", t);
	srand(seed);
	while(t --)
	{
		for(int i = 0; i < n; i ++)
			printf("%c", rand() % 10 + 'a');
		printf("\n");
	}
}
