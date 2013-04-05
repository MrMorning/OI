#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 1; i <= m; i ++)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10000000 + 1);
}
