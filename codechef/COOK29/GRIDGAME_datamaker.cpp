#include <cstdio>
#include <cstring>
#include <cstdlib>
int N, Q, seed, TST;
bool ban[1111][1111];
int r() {
	return rand() % 10;
}
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &TST, &N, &Q, &seed);
	srand(seed);
	printf("%d\n", TST);
	while ( TST -- ) {
		memset(ban, 0, sizeof(ban));
		printf("%d\n", N);
		for ( int i = 0; i < N; i ++ ) {
			int x = r(), y = r();
			printf("%d %d\n", x, y);
			ban[x][y] = true;
		}
		printf("%d\n", Q);
		for ( int i = 0; i < Q; i ++ ) {
			int x = r(), y = r();
			while ( ban[x][y] )
				x = r(), y = r();
			printf("%d %d\n", x, y);
		}
	}
}
