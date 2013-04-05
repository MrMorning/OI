#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, seed;
int perm[666*666], a[666][666], top[666][666], left[666][666];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	for ( int i = 1; i <= n*n; i ++ )
		perm[i] = i;
	random_shuffle(perm+1,perm+1+n*n);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) 
			a[i][j] = perm[(i-1)*n+j];
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) {
			for ( int k = 1; k <= j; k ++ )
				left[i][j] += a[i][k] > a[i][j];
			for ( int k = 1; k <= i; k ++ )
				top[i][j] += a[k][j] > a[i][j];
		}
	printf("%d\n", n);
	for ( int i = 1; i <= n;i ++, printf("\n") )
		for ( int j = 1; j <= n; j++ )
			printf("%d ", top[i][j]);
	printf("\n");
	for ( int i = 1; i <= n;i ++, printf("\n") )
		for ( int j = 1; j <= n; j++ )
			printf("%d ", left[i][j]);
}
