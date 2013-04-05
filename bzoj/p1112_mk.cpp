#include <cstdio>
#include <cstdlib>
int n, seed, k;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n,&k,  &seed);
	srand(seed);
	printf("%d %d\n", n, k);
	while (n --)
		printf("%d\n", rand() % 1000000 + 1);
}
