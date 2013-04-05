#include <cstdio>
#include <cstdlib>
int seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	int r = rand() % 10 + 1;
	int a, b, c;
	while ( 1 ) {
		a = rand() % 10 - rand() % 10,
		  b = rand() % 10 - rand() % 10,
		  c = rand() % 10 - rand() % 10;
		if ( a*a+b*b+c*c > r*r ) break;
	}
	printf("%d\n", r);
	printf("%d %d %d\n", a, b, c);
	while ( 1 ) {
		a = rand() % 10 - rand() % 10,
		  b = rand() % 10 - rand() % 10,
		  c = rand() % 10 - rand() % 10;
		if ( a*a+b*b+c*c > r*r ) break;
	}
	printf("%d %d %d\n", a, b, c);
}
