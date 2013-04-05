#include <cstdio>
#include <cstdlib>
int n, seed;

int rv() {
	return rand()%10-rand()%10;
}

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	while ( n -- ) 
		printf("%d %d %d %d\n", rv(), rv(), rv(), rv());
}
