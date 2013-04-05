#include <cstdio>
#include <cstdlib>
int len, seed, TST;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &TST, &len, &seed);
	srand(seed);
	printf("%d\n", TST);
	while ( TST -- ) {
		int sz = rand() % 10 + 1;
		for ( int i = 0; i < len; i ++ )
			printf("%c", rand() % sz + 'a');
		printf("\n");
	}
}
