#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, m, seed;
int a[11111];

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ )
		a[i] = i;
	random_shuffle(a, a + n);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", a[i] + 1);
}
