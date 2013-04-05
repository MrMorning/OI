#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int T, N, Q, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &T, &N, &Q, &seed);
	srand(seed);
	printf("%d\n", T);
	while ( T -- ) {
		printf("%d %d\n", N, Q);
		for ( int i = 0; i < N; i ++ )
			printf("%d ", rand() % 10 - rand() % 10);
		printf("\n");
		for ( int q = 0; q < Q; q ++ ) {
			int t = rand() % 2;
			int l = rand() % N + 1, r = rand() % N + 1;
			if ( l > r ) {
				swap(l, r);
			}
			if ( t == 0 ) 
				printf("a %d %d %d\n", l, r, rand() % 10 - rand() % 10);
			else
				printf("q %d %d\n", l, r);
		}
	}
}
