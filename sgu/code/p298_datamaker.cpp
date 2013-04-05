#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	while ( m -- ) {
		int u = rand() % n + 1, 
			v = rand() % n + 1;
		while ( u == v ) {
		u = rand() % n + 1, 
			v = rand() % n + 1;
		}
		printf("%d %d %d\n", u, v, rand() % 1000);
	}
}
