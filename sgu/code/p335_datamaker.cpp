#include <cstdio>
#include <cstdlib>
int seed, range;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &range, &seed);
	srand(seed);
	int H = rand() % range + 1, W = rand() % range + 1;
	while ( H == 1 && W == 1 )
		H = rand() % range + 1, W = rand() % range + 1;
	printf("%d %d\n", H, W);
	int x1 = rand() % H + 1, y1 = rand() % W + 1;
	int x2 = rand() % H + 1, y2 = rand() % W + 1;
	while ( x2 == x1 && y2 == y1 )
		x2 = rand() % H + 1, y2 = rand() % W + 1;
	printf("%d %d\n", x1, y1);
	printf("%d %d\n", x2, y2);
	printf("%s\n", rand() & 1 ? "C" : "T");
}
