#include <cstdio>
#include <cstdlib>
int seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	for ( int i = 0; i < 4; i ++ )
		printf("%d ", rand() % 500000+ 1);
}
