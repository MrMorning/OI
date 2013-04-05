#include <cstdio>
#include <cstdlib>
int seed;
int r() { return rand() % 99 + 1; }
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	int a = r(), b = r(), c = r();
	while ( !(a + b > c && b + c > a && c + a > b
				&& a * a + b * b > c * c
			   	&& a * a + c * c > b * b
				&& c * c + b * b > a * a) )
		a = r(), b = r(), c = r();
	printf("%d %d %d %d\n", a, b, c, r());
	printf("0 0 0 0\n");
}
