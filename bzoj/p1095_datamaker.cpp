#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for (int i = 1; i < n; i ++)
		printf("%d %d\n", i + 1, rand() % i + 1);
	printf("%d\n", m);
	while (m --) {
		int t = rand() % 2;
		if (t == 0)
			puts("G");
		else
			printf("C %d\n", rand() % n + 1);
	}
}
