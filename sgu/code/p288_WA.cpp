#include <cstdio>
int board[2010][2010];
int n;
int main() {
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	scanf("%d", &n);
	for ( int x = 1; x <= n - 1; x ++ ) {
		int y = x + 1;
		board[x][y] = board[y][x] = ((x - 1) & 1) + 1;
	}
	for ( int y = 3; y <= n; y ++ ) {
		for ( int x = 1; x <= n - 2 - (y - 3); x ++ )
			board[x][y + x - 1] = board[y + x - 1][x] = y;
	}
	if ( n % 2 == 0 && n > 2 )
		board[1][n] = board[n][1] = 2;

	printf("%d\n", (n & 1) ? n : n - 1);
	for ( int i = 1; i <= n; i ++ , puts("") )
		for ( int j = 1; j <= n; j ++ )
			printf("%d ", board[i][j]);
}
