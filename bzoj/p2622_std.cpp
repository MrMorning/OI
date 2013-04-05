#include <cstdio>
#include <cstring>
#include <cstdlib>
int N, M, K, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &N, &M, &K, &seed);
	srand(seed);
	printf("%d %d %d\n", N, M, K);
	while ( M -- ) 
		printf("%d %d %d\n", rand() % N, rand() % N, rand() % 1000);
	for ( int i = 0; i < K; i ++ ) {
		printf("%d\n", rand() % N);
	}

}
