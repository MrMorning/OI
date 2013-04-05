#include <cstdio>
int board[2010][2010];
int n;
int main() {
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	scanf("%d", &n);
	if ( n == 1 ) {
		printf("0\n0\n");
		return 0;
	}

	if ( n & 1 ) {
		for ( int i = 1; i <= n; i ++ )
			for ( int j = 1; j <= n; j ++ )
				if ( i != j )
					board[i][j] = (i + j) % n + 1;
	} else {
		for ( int i = 1; i <= n; i ++ ) {
			for ( int j = i + 1; j < n; j ++ ) 
				board[i][j] = board[j][i] = (i + j) % (n - 1) + 1;
			if ( i != n )
				board[i][n] = board[n][i] = (i + i) % (n - 1) + 1;
		}
	}

	printf("%d\n", (n & 1) ? n : n - 1);
	for ( int i = 1; i <= n; i ++ , puts("") )
		for ( int j = 1; j <= n; j ++ )
			printf("%d ", board[i][j]);
}
