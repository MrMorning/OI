#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef double val_t;

val_t bino[111][111], fact[111], d[111], f[111][111];

int main() {
	freopen("t.in", "r", stdin);

	bino[0][0] = 1;
	for ( int i = 1; i <= 100; i ++ ) {
		bino[i][0] = 1;
		for ( int j = 1; j <= i; j ++ )
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
	}
	fact[0] = 1;
	for ( int i = 1; i <= 100; i ++ )
		fact[i] = fact[i-1] * i;
	d[0] = 1, d[1] = 0;
	for ( int i = 2; i <= 100; i ++ )
		d[i] = (i-1)*(d[i-1]+d[i-2]);

	int n;
	scanf("%d", &n);

	val_t ans = 0;
	for ( int l = 2; l <= n; l ++ ) {
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for ( int i = 1; i <= n; i ++ )
			for ( int j = 0; j*l <= i; j ++ ) {
				for ( int t = 2; t <= min(l, i); t ++ )
					if ( j-(t==l) >= 0 )
						f[i][j] += f[i-t][j-(t==l)]*bino[i-1][t-1]*fact[t-1];
			}
		for ( int j = 1; j*l <= n; j ++ )
			ans += f[n][j]*j*l;
	}
	ans /= d[n];
	printf("%.10lf\n", ans);
}
