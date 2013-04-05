#include <cstdio>
#include <cstdlib>
int main() {
	freopen("t.in", "w", stdout);
	int N, L, seed;
	scanf("%d%d%d", &N, &L, &seed);
	srand(seed);
	printf("%d\n", N);
	while ( L -- )
		printf("%c", rand() % 2 == 0 ? 'a' : 'b');
	puts("");
	for ( int i = 1; i <= N; i ++ ) {
		int l = rand() % 5 + 1;
		printf("%d ", l);
		while ( l -- ) {
			int t = rand() % 2;
			if ( i == 1 || (t & 1) ) 
				printf("%c ", rand() % 2 == 0 ? 'a' : 'b');
			else
				printf("%d ", rand() % (i - 1) + 1);
		}
		puts("");
	}
}
