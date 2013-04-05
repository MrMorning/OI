#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int la, lb, seed, a[1111111], b[1111111];

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &la, &lb, &seed);
	srand(seed);
	printf("%d %d\n", la, lb);
	for ( int i = 1; i <= la; i ++ )
		a[i] = i;
	for ( int i = 1; i <= lb; i ++ )
		b[i] = i;
	random_shuffle(a + 1, a + 1 + la);
	random_shuffle(b + 1, b + 1 + lb);
	for ( int i = 1; i <= la; i ++ )
		printf("%d ", a[i]);
	puts("");
	for ( int i = 1; i <= lb; i ++ )
		printf("%d ", b[i]);
	puts("");
}
