#include <cstdio>
#include <cstdlib>
const int offset[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int n, m, n_try, seed;
bool mark[1111][1111], setr[1111], setc[1111];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &n_try, &seed);
	srand(seed);
	printf("%d %d\n", n, m);

	while ( n_try -- ) {
		int x = rand() % n, y = rand() % m;
		if ( setr[x] || setc[y] )
			continue;
		bool fail = false;
		for ( int d = 0; d < 8; d ++ ) {
			int nx = x + offset[d][0],
				ny = y + offset[d][1];
			if ( 0 <= nx && nx < n )
				if ( 0 <= ny && ny < m ) {
					if ( mark[nx][ny] ) {
						fail = true;
						break;
					}
				}
		}
		if ( !fail ) {
			mark[x][y] = true;
			setr[x] = setc[y] = true;
		}
	}

	for ( int i = 0; i < n; i ++ , puts(""))
		for ( int j = 0; j < m; j ++ ) {
			printf("%c", mark[i][j] ? 'X' : '.');
		}
}
