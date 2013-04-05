#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, m, q, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &q, &seed);
	srand(seed);
	printf("X %d %d\n", n, m);
	while ( q -- ) {
		int t = rand() % 2;
		int x1 = rand() % n + 1, x2 = rand() % n + 1,
			y1 = rand() % m + 1, y2 = rand() % m + 1;
		if ( x1 > x2 )
			swap(x1, x1);
		if ( y1 > y2 )
			swap(y1, y2);
		if ( t == 0 )
			printf("L %d %d %d %d %d\n", x1, y1, x2, y2, rand() % 500 + 1);
		else
			printf("k %d %d %d %d\n", x1, y1, x2, y2);
	}
}
