#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
int ans = inf;
char board[22][22];
int cover[22][22];
int mark[3][3];
bool fig[9][3][3];
pair<int, int> ctr[9];
int nRow, nCol, nFig;
int ansOut1[22][22], ansOut2[3][3];
bool onBoard(int x, int y) {
	return 0 <= x && x < nRow && 0 <= y && y < nCol;
}
bool dfs2(int i) {
	if ( i == nFig ) 
		return true;
	for ( int x = 0; x < nRow; x ++ )
		for ( int y = 0; y < nCol; y ++ )
			if ( board[x][y] == 'X' && !cover[x][y] ) {
				bool fail = false;
				int nx = x - ctr[i].first,
					ny = y - ctr[i].second;
				for ( int kx = 0; kx < 3 && !fail; kx ++ )
					for ( int ky = 0; ky < 3 && !fail; ky ++ )
						if ( fig[i][kx][ky] && (!onBoard(nx+kx,ny+ky) || board[nx+kx][ny+ky] == '.' || cover[nx+kx][ny+ky]) ) 
							fail = true;
				if ( fail ) 
					continue;
				for ( int kx = 0; kx < 3; kx ++ )
					for ( int ky = 0; ky < 3; ky ++ )
						if ( fig[i][kx][ky] )
							cover[nx+kx][ny+ky] = i + 1;
				if ( dfs2(i + 1) )
					return true;
				for ( int kx = 0; kx < 3; kx ++ )
					for ( int ky = 0; ky < 3; ky ++ )
						if ( fig[i][kx][ky] )
							cover[nx+kx][ny+ky] = 0;
			}
	return false;

}
int stat = 0;
bool painted[3][3];

void paint(int x, int y, int c) {
	painted[x][y] = true;
	for ( int dir = 0; dir < 4; dir ++ ) {
		int nx = x + dx[dir],
			ny = y + dy[dir];
		if ( 0 <= nx && nx < 3 && 0 <= ny && ny < 3 )
			if ( mark[nx][ny] == c && !painted[nx][ny] ) 
				paint(nx, ny, c);
	}
}

bool check() {
	static bool done[9];
	memset(done, 0, sizeof(done));
	for ( int x = 0; x < 3; x ++ )
		for ( int y = 0; y < 3; y ++ ) {
			int c = mark[x][y];
			if ( !done[c] ) {
				done[c] = true;
				memset(painted, 0, sizeof(painted));
				paint(x, y, c);
				for ( int tx = 0; tx < 3; tx ++ )
					for ( int ty = 0; ty < 3; ty ++ )
						if ( mark[tx][ty] == c && !painted[tx][ty] ) 
							return false;
			}
		}
	return true;
}

void update(int cnt) {
	if ( !check() || cnt >= ans )
		return;
	nFig = cnt;
	memset(fig, 0, sizeof(fig));
	for ( int x = 0; x < 3; x ++ )
		for ( int y = 0; y < 3; y ++ ) {
			fig[mark[x][y]][x][y] = true;
			ctr[mark[x][y]] = make_pair(x, y);
		}
	memset(cover, 0, sizeof(cover));
	if ( dfs2(0) ) {
		ans = cnt;
		memcpy(ansOut1, cover, sizeof(cover));
		memcpy(ansOut2, mark, sizeof(mark));
	}
}

void dfs(int x, int y, int cnt) {
	if ( y == 3 ) {
		dfs(x + 1, 0, cnt);
		return;
	}
	if ( x == 3 ) {
		update(cnt);
		return;
	}
	for ( int t = 0; t <= cnt; t ++ ) {
		mark[x][y] = t;
		dfs(x, y + 1, cnt + (t == cnt));
		mark[x][y] = -1;
	}
}

int main() {
	memset(board, '.', sizeof(board));
	scanf("%d%d", &nRow, &nCol);
	for ( int i = 0; i < nRow; i ++ ) {
		scanf("%s", board[i]);
		board[i][nCol] = '.';
	}
	memset(mark, -1, sizeof(mark));
	dfs(0, 0, 0);
	printf("%d\n", ans);
	for ( int i = 0; i < nRow; i ++, puts("") )
		for ( int j = 0; j < nCol; j ++ )
			if ( ansOut1[i][j] == 0 )
				printf(".");
			else
				printf("%c", 'A' - 1 + ansOut1[i][j]);
	puts("");
	for ( int i = 0; i < 3; i ++, puts("") )
		for ( int j = 0; j < 3; j ++ )
			printf("%c", 'A' + ansOut2[i][j]);
}
