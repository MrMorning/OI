#include <cstdio>
#include <cmath>
#define LOSE 0
#define WIN 1
#define DRAW 2
int f[33333][33];
bool fine[33333][33];
int a, b, p;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &a, &b, &p);
	if ( a == 1 && (1<<b) >= p ) {
	   puts("Missing");	
	   return 0;
	} else if ( b == 1 && a * a >= p ) {
		if ( (a+p+1) % 2 == 0 ) puts("Stas");
		else puts("Masha");
		return 0;
	}
	int n = (int)ceil(sqrt(p)), m = (int)ceil(log(p)/log(2));
	for ( int i = 1; i <= n; i ++ ) {
		int tmp = 1;
		for ( int j = 1; j <= m; j ++ ) {
			if ( (long long)tmp * i < p )
				tmp *= i, fine[i][j] = true;
			else fine[i][j] = false;
		}
	}
	f[1][m+1] = DRAW;
	f[n+1][1] = (n+1+p+1) % 2 == 0 ? LOSE : WIN;
	for ( int i = 2; i <= n; i ++ )
		f[i][m+1] = WIN;
	for ( int j = 2; j <= m; j ++ )
		f[n+1][j] = WIN;
	for ( int i = n; i >= 1; i -- )
		for ( int j = m; j >= 1; j -- ) 
			if ( fine[i][j] ) {
				if ( f[i+1][j] == LOSE || f[i][j+1] == LOSE )
					f[i][j] = WIN;
				else if ( f[i+1][j] == WIN && f[i][j+1] == WIN )
					f[i][j] = LOSE;
				else
					f[i][j] = DRAW;
			} else f[i][j] = WIN;
	if ( f[a][b] == WIN ) puts("Masha");
	else if ( f[a][b] == LOSE ) puts("Stas");
	else
		puts("Missing");
}
