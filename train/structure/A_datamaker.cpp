#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, m ,seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0 ;i < n; i ++ )
		printf("%d ", rand() % 10000 - 5000);
	puts("");
	printf("%d\n", m);
	while ( m -- ) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r )
			swap(l, r);
		printf("%d %d\n", l ,r);
	}
}
