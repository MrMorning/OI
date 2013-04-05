#include <cstdio>
#include <cstdlib>
int n;
int main()
{
	freopen("t.in", "w", stdout);
	printf("1\n");
	scanf("%d", &n);
	srand(n);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
	{
		int len = rand() % 50 + 1;
		for(int j = 0; j < len; j ++)
			printf("%c", rand() % 26 + 'a');
		printf("\n");
	}
	for(int i = 0; i < 1000000; i ++)
		printf("%c", rand() % 26 + 'a');
	printf("\n");
}
