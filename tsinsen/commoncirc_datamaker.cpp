#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	printf("%d\n", n);
	srand(seed);
	while ( n -- ) {
		printf("%d %d %d\n", rand()%2, rand() % 10+1, rand()%10+1);
	}
}
