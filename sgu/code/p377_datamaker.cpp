#include <cstdio>
#include <cstdlib>
int main() {
	freopen("t.in", "w", stdout);
	int seed;
	scanf("%d", &seed);
	srand(seed);
	printf("%d %d\n", rand()%1000+2, rand()%1000+2);
}
