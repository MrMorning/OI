#include <cstdio>
#include <cstdlib>
int n, r, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &r, &seed);
	srand(seed);
	printf("%d %d\n", n, r);
	while ( n -- ) {
		int x1, y1, x2, y2;
		x1 = rand() % (r+1) - rand() % (r+1),
			y1 = rand() % (r+1) - rand() % (r+1);
		while ( x1*x1+y1*y1 > r*r )
		x1 = rand() % (r+1) - rand() % (r+1),
			y1 = rand() % (r+1) - rand() % (r+1);

		do {
		x2 = rand() % (r+1) - rand() % (r+1),
			y2 = rand() % (r+1) - rand() % (r+1);

		} while ( (x1==x2&&y1==y2) || (x2*x2+y2*y2>r*r) );

		int a = y2-y1,b = x1-x2, c = -(a*x1+b*y1);
		printf("%d %d %d\n", a, b, c);
	}
}
