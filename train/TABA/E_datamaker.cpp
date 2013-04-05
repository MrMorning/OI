#include <cstdio>
#include <cstdlib>
int T, n, tot, seed;
int memo[20000];

void pstr(int len) {
	while ( len -- )
		printf("%c", rand() % 26 + 'a');
}

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &T, &n, &tot, &seed);
	srand(seed);
	printf("%d\n", T);
	while ( T -- ) {
		int left = tot;
		printf("%d\n", n);
		for ( int i = 0; i < n; i ++ ) {
			int m = rand() % (left - (n - 1 - i)) + 1;
			memo[i] = m;
			left -= m;
		}

		for ( int i = n - 1; i >= 0; i -- ) {
			pstr(memo[i]);
			printf(" %d\n", rand() % 2000 -1000);
		}
	}
}
