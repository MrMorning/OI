#include <cstdio>
#include <cstdlib>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	while ( n -- ) {
		int t = rand() % 3;
		if ( t == 0 )
			printf("%c", rand() % 26 + 'a');
		else if ( t == 1 )
			printf("L");
		else
			printf("R");
	}
}
