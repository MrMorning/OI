#include <cstdio>
#include <cstdlib>
int T, seed;
int main() {
	freopen("lucky2.in", "w", stdout);
	scanf("%d%d", &T, &seed);
	srand(seed);
	printf("%d\n", T);
	while ( T -- ) {
		int len1 = rand() % 1000 + 1,
			len2 = len1 + rand() % (1001 - len1) + 1;
		while ( len1 -- )
			printf("%d", rand() % 9 + 1);
		printf(" ");
		while ( len2 -- )
			printf("%d", rand() % 9 + 1);
		printf("\n");
	}
}
