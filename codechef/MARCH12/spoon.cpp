#include <cstdio>
#include <cstring>
char mat[111][111];
const char SPOON[5] = {'S', 'P', 'O', 'O', 'N'};
void solve() {
	int R, C;
	scanf("%d%d", &R, &C);
	for ( int i = 0; i < R; i ++ ) {
		scanf("%s", mat[i]);
		for ( int j = 0; j < C; j ++ )
			if ( 'a' <= mat[i][j] && mat[i][j] <= 'z' )
				mat[i][j] = mat[i][j] - 'a' + 'A';
	}
	for ( int i = 0; i < R; i ++ )
		for ( int j = 0; j < C - 4; j ++ )
			if ( strncmp(mat[i] + j, SPOON, 5) == 0 ) {
				printf("There is a spoon!\n");
				return;
			}
	for ( int i = 0; i < R - 4; i ++ )
		for ( int j = 0; j < C; j ++ ) {
			static char ts[10];
			for ( int t = 0; t < 5; t ++ )
				ts[t] = mat[i + t][j];
			if ( strncmp(ts, SPOON, 5) == 0 ) {
				printf("There is a spoon!\n");
				return;
			}
		}
	printf("There is indeed no spoon!\n");
}

int main() {
	freopen("spoon.in", "r", stdin);
	freopen("spoon.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) 
		solve();
}
