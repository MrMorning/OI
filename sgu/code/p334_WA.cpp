#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int ans = inf;
char board[22][22];
int cover[22][22];
int mark[3][3];
bool fig[9][3][3];
pair<int, int> ctr[9];
int nRow, nCol, nFig;
bool dfs2(int i) {
	if ( i == nFig ) 
		return true;
	for ( int x = 0; x < nRow; x ++ )
		for ( int y = 0; y < nCol; y ++ )
			if ( board[x][y] == 'X' && !cover[x][y] ) {
				bool fail = false;
				int nx = x - ctr[i].first,
					ny = y - ctr[i].second;
				if ( !(0 <= nx && 0 <= ny) ) 
					continue;
				for ( int kx = 0; kx < 3 && !fail; kx ++ )
					for ( int ky = 0; ky < 3 && !fail; ky ++ )
						if ( fig[i][kx][ky] && (board[nx+kx][ny+ky] == '.' || cover[nx+kx][ny+ky]) ) 
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
void update(int cnt) {
	if ( cnt >= ans )
		return;
	nFig = cnt;
	for ( int x = 0; x < 3; x ++ )
		for ( int y = 0; y < 3; y ++ ) {
			fig[mark[x][y]][x][y] = true;
			ctr[mark[x][y]] = make_pair(x, y);
		}
	memset(cover, 0, sizeof(cover));
	if ( mark[0][0] == 0 && mark[0][1] == 0 && mark[0][2] == 1
			&& mark[1][0] == 1 && mark[1][1] == 1 && mark[1][2] == 1
			&& mark[2][0] == 1 && mark[2][1] == 1 && mark[2][2] == 2 )
		puts("HA");
	if ( dfs2(0) ) 
		ans = cnt;
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
	if ( x - 1 >= 0 ) {
		mark[x][y] = mark[x - 1][y];
		dfs(x, y + 1, cnt);
		mark[x][y] = -1;
	}
	if ( y - 1 >= 0 ) {
		if ( !(x - 1 >= 0 && mark[x][y - 1] == mark[x - 1][y]) ) { 
			mark[x][y] = mark[x][y - 1];
			dfs(x, y + 1, cnt);
			mark[x][y] = -1;
		}
	}
	mark[x][y] = cnt;
	dfs(x, y + 1, cnt + 1);
	mark[x][y] = -1;
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	memset(board, '.', sizeof(board));
	scanf("%d%d", &nRow, &nCol);
	for ( int i = 0; i < nRow; i ++ ) {
		scanf("%s", board[i]);
		board[i][nCol] = '.';
	}
	memset(mark, -1, sizeof(mark));
	dfs(0, 0, 0);
	printf("%d\n", ans);
}
