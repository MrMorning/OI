#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % 1000 + 1);
	printf("\n%d\n", m);
	for ( int i = 0; i < m; i ++ ) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r )
			swap(l, r);
		int k = rand() % (r - l + 1) + 1;
		printf("%d %d %d\n", l, r, k);
	}
}
