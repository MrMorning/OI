#include <cstdio>
#include <cstdlib>
int n, k, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	srand(seed);
	printf("%d %d\n", n, k);
	while (n --) 
		printf("%d ", rand() % 100000007);
}
