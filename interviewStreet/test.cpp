#include <cstdio>
int f[33][33][33];
int main() {
	freopen("t.in", "r", stdin);
	f[0][0][0] = 1;
	for ( int i = 0; i < 30; i ++ )
		for ( int j = 0; j <= 30; j ++ ) 
			for ( int k = 0; k <= 30; k ++ ) {
				if ( f[i][j][k] ) {
					for ( int x = k; x <= 30 - j; x ++ )
						f[i + 1][j + x][x] += f[i][j][k];
				}
			}
	int res = 0;
	for ( int k = 0; k <= 30; k ++ ) 
		res += f[30][30][k];
	printf("%d\n", res);
}
