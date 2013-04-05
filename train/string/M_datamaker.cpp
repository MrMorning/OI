#include <cstdio>
#include <cstdlib>
int T, n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &T, &n, &seed);
	srand(seed);
	for ( int j = 0; j < T; j ++ ) {
		int m = rand() % n + 2;
		for ( int i = 0; i < m; i ++ )
			printf("%c", rand() % 26 + 'a');
		puts("");
	}
	puts("\n#");
}
