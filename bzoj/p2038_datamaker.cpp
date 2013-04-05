#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, m, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ )
		printf("%d ", rand() % n + 1);
	puts("");
	for ( int i = 0; i < m; i ++ ) {
		int a = rand() % n + 1, b = rand() % n + 1;
		if ( a > b ) 
			swap(a, b);
		printf("%d %d\n", a, b);
	}
}
