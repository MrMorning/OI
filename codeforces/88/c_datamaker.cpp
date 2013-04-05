#include <cstdio>
#include <cstdlib>
int seed, n;
bool e[5000][5000];
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
		for(int j = i + 1; j < n; j ++)
			e[i][j] = rand() % 2;
	for(int i = 0; i < n; i ++, printf("\n"))
		for(int j = 0; j < n; j ++)
			if(i < j)
				printf("%d", e[i][j]);
			else if(i == j)
				printf("0");
			else
				printf("%d", !e[j][i]);
}
