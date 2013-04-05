#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, seed;
inline int randVal()
{
	return rand() % 5000 + 1;
}
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			printf("%d ", randVal());
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			printf("%d ", randVal());
	for(int i = 1; i < n; i ++)
		for(int j = 1; j <= m; j ++)
			printf("%d ", randVal());
	for(int i = 1; i < n; i ++)
		for(int j = 1; j <= m; j ++)
			printf("%d ", randVal());
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < m; j ++)
			printf("%d ", randVal());
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < m; j ++)
			printf("%d ", randVal());
}
