#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int dx[8] = {-1, 1, 0, 0, 1, -1, -1, 1};
const int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int n, m;
char board[333][333];
int early[333][333][2];
int startX, startY;

void walk(int &x, int &y, int dir) {
	x += dx[dir], y += dy[dir];
}

void prework() {
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%s", board[i] + 1);
		for ( int j = 1; j <= n; j ++ ) {
			if ( board[i][j] == 'Q' ) {
				startX = i, startY = j;
				board[i][j] = '.';
			}
		}
	}
	for ( int i = 0; i <= n + 1; i ++ ) {
		board[i][0] = board[i][n + 1] = 'W';
		board[0][i] = board[n + 1][i] = 'W';
	}
}

void expand(int x, int y, int t) { 
	static bool fine[8];
	for ( int dir = 0; dir < 8; dir ++ ) {
		int p = x, q = y;
		do {
			walk(p, q, dir);
			if ( board[p][q] == 'W' )
				break;
			early[p][q][t ^ 1] = min(early[p][q][t ^ 1], early[x][y][t] + 1);
			if ( early[p][q][t] == early[x][y][t] )
				break;
		} while ( board[p][q] == '.' );
	}
	memset(fine, 0, sizeof(fine));
	if ( board[x][y] == 'B' && early[x][y][t] <= m ) {
		for ( int dir = 0; dir < 8; dir += 2 ) {
			int cnt = 0;
			int p = x, q = y; walk(p, q, dir);
			cnt += board[p][q] != 'W';

			p = x, q = y; walk(p, q, dir ^ 1);
			cnt += board[p][q] != 'W';

			if ( cnt == 2 ) 
				fine[dir] = fine[dir ^ 1] = true;
		}

		for ( int dir = 0; dir < 8; dir ++ )
			if ( fine[dir] ) {
				int p = x, q = y;
				do {
					walk(p, q, dir);
					if ( board[p][q] == 'W' )
						break;
					early[p][q][t] = min(early[p][q][t], early[x][y][t] + 2);
				} while ( board[p][q] == '.' );
			}
	}
}

void solve() {
	int cnt = 0;
	for ( int dir = 0; dir < 8; dir ++ ) {
		int p = startX, q = startY;
		walk(p, q, dir);
		cnt += board[p][q] == 'W';
	}
	if ( cnt == 8 ) {
		printf("%d\n", m == 0);
		return;
	}
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ )
			early[i][j][0] = early[i][j][1] = m + 1;
	early[startX][startY][0] = 0;
	for ( int t = 0; t < m; t ++ ) {
		for ( int x = 1; x <= n; x ++ )
			for ( int y = 1; y <= n; y ++ )
				if ( early[x][y][t & 1] == t )
					expand(x, y, t & 1);
	}

	int ans = 0;
	for ( int x = 1; x <= n; x ++ )
		for ( int y = 1; y <= n; y ++ )
			ans += early[x][y][m & 1] <= m;
	printf("%d\n", ans);
}

int main() {
	prework();
	solve();
}
