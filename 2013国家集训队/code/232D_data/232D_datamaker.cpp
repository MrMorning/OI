#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define TEST_NUM "20"
#define LIM 100000
using namespace std;

int n, m,seed;
int out[111111];
int main() {
	freopen(TEST_NUM ".in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 0; i < n / 2; i ++ )
		printf("%d ", i);
	for ( int i = n / 2; i < n; i ++ )
		printf("%d ", n-i);
	printf("\n%d\n", m);
	for ( int i = 0; i < m; i ++ ) {
		int l, r;
		l = rand() % n + 1, r = l + min(LIM, rand() % (n+1-l));
		if ( r > n ) r = n;
		if ( l > r )
			swap(l, r);
		printf("%d %d\n", l, r);
	}
}
