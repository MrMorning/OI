#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0}; 
int n, m;
char board[55][55];
bool vis[55][55], blocked[55][55];
int ans = 0x3f3f3f3f;

struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
	Point walk(int dir) {
		return Point(x + dx[dir], y + dy[dir]);
	}
	bool valid() {
		return 0 <= x && x < n && 0 <= y && y < m;
	}
};

void dfs(int x, int y) {
	vis[x][y] = true;
	for ( int dir = 0; dir < 4; dir ++ ) {
		Point nxt = Point(x, y).walk(dir);
		if ( nxt.valid() && board[nxt.x][nxt.y] == '#' && !vis[nxt.x][nxt.y] && !blocked[nxt.x][nxt.y] ) 
			dfs(nxt.x, nxt.y);
	}
}

int countBits(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	int sx, sy;
	for ( int i = 0; i < n; i ++ ) {
		scanf("%s", board[i]);
		for ( int j = 0; j < m; j ++ ) 
			if ( board[i][j] == '#' )
				sx = i, sy = j;
	}
	memset(vis, 0, sizeof(vis));
	dfs(sx, sy);
	int visCnt = 0;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			if ( vis[i][j] )
				visCnt ++;
	if ( visCnt <= 2 ) {
		puts("-1");
		return 0;
	}

	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ ) 
			if ( board[i][j] == '#' ) {
				Point cur(i, j);
				for ( int s = 0, lim = 1 << 4; s < lim; s ++ )
					if ( countBits(s) == 1 || countBits(s) == 2 ) {
						bool fail = false;
						for ( int k = 0; !fail && k < 4; k ++ )
							if ( s & (1 << k) ) {
								Point adj = cur.walk(k);
								if ( !adj.valid() || board[adj.x][adj.y] != '#' ) {
									fail = true;
									continue;
								}
							}
						if ( fail )
							continue;
						memset(blocked, 0, sizeof(blocked));
						for ( int k = 0; !fail && k < 4; k ++ )
							if ( s & (1 << k) ) {
								Point adj = cur.walk(k);
								blocked[adj.x][adj.y] = true;
							}
						bool found = false;
						for ( int tx = 0; !found && tx < n; tx ++ )
							for ( int ty = 0; !found && ty < m; ty ++ )
								if ( board[tx][ty] == '#' && !blocked[tx][ty] ) {
									found = true;
									memset(vis, 0, sizeof(vis));
									dfs(tx, ty);
								}
						found = false;
						for ( int tx = 0; !found && tx < n; tx ++ )
							for ( int ty = 0; !found && ty < m; ty ++ )
								if ( board[tx][ty] == '#' && !blocked[tx][ty] && !vis[tx][ty] ) 
									ans = min(ans, countBits(s));
					}
			}
	printf("%d\n", ans);
}
