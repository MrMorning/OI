#include <cstdio>
#include <cstring>
#include <cstdlib>
int n, m, seed;
char board[333][333];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n%d\n", n, m);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) {
			int t = rand() % 10;
			if ( t == 0 )
				board[i][j] = 'W';
			else if ( t == 1 )
				board[i][j] = 'B';
			else 
				board[i][j] = '.';
		}
	int stX = rand() % n + 1, stY = rand() % n + 1;
	board[stX][stY] = 'Q';
	for ( int i = 1; i <= n; i ++ )
		printf("%s\n", board[i] + 1);
}
