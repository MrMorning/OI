#include <cstdio>
#include <cstdlib>
int n, seed, cnt;
bool a[101][101];
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	int m = rand() % (n * n / 2); 
	for(int i = 1; i <= m; i ++)
		a[rand() % n + 1][rand() % n + 1] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++)
			if(a[i][j])
				cnt ++;
	printf("%d %d\n", n, cnt);
	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++)
			if(a[i][j])
				printf("%d %d %d\n", i, j, rand() % 5 + 1);
}
