#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cassert>
#define mp(x, y) make_pair(x, y)
using namespace std;

bool vis[33][33];
char bd[33][33];
int color[33][33], samp[33][33];
int cnt[15];
int n, m;
bool used[7][7];
pair<int, int> par[33][33], blk[15];
int tot = 0, nBlk = 0;

inline void mark(int x, int y) {
	int t1 = color[x][y], t2 = color[par[x][y].first][par[x][y].second];
	if ( t1 != -1 && t2 != -1 )
		used[t1][t2] = used[t2][t1] = true;
}

inline void unmark(int x, int y) {
	int t1 = color[x][y], t2 = color[par[x][y].first][par[x][y].second];
	if ( t1 != -1 && t2 != -1 )
		used[t1][t2] = used[t2][t1] = false;
}

inline bool check(int x, int y) {
	int t1 = color[x][y], t2 = color[par[x][y].first][par[x][y].second];
	if ( t1 == -1 || t2 == -1 ) return true;
	return !used[t1][t2];
}

bool bruteCheck() {
	static int cnt[7][7];
	memset(cnt, 0, sizeof(cnt));
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( isalpha(bd[i][j]) ) 
				cnt[color[i][j]][color[par[i][j].first][par[i][j].second]]++;
	for ( int i = 0; i <= 6; i ++ )
		for ( int j = 0; j <= 6; j ++ )
			if ( i == j ) {
				if ( cnt[i][j] != 2 )
					return false;
			} else {
				if ( cnt[i][j] != 1 ) return false;
			}
	return true;
}

void dfs(int i, int j) {
	if ( i == 15 ) {
		if ( bruteCheck() ) {
			tot++;
		//	for ( int i = 1; i <= n; i ++, puts("") )
		//		for ( int j = 1; j <= m; j ++ )
		//			if ( color[i][j] == -1 ) printf(".");
		//			else printf("%d", color[i][j]);
		//	puts("");
			if ( tot == 1 ) 
				memcpy(samp, color, sizeof(color));
		}
		return;
	}
	int x = blk[i].first, y = blk[i].second;
	for ( int c = 0; c <= min(6, j); c ++ ) 
		if ( cnt[c] < 2 ) {
			for ( int dx = 0; dx <= 1; dx ++ )
				for ( int dy = 0; dy <= 1; dy ++ ) 
					color[x+dx][y+dy] = c;
			if ( check(x, y) && check(x, y+1) && check(x+1, y) && check(x+1, y+1) ) {
				mark(x, y), mark(x, y+1), mark(x+1, y), mark(x+1, y+1);
				cnt[c]++;
				dfs(i+1, j+(c==j));
				cnt[c]--;
				unmark(x, y), unmark(x, y+1), unmark(x+1, y), unmark(x+1, y+1);
			}
			for ( int dx = 0; dx <= 1; dx ++ )
				for ( int dy = 0; dy <= 1; dy ++ )
					color[x+dx][y+dy] = -1;
		}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) 
		scanf("%s", bd[i]+1);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			if ( !vis[i][j] && isalpha(bd[i][j]) ) {
				blk[++nBlk] = mp(i, j);
				for ( int dx = 0; dx <= 1; dx ++ )
					for ( int dy = 0; dy <= 1; dy ++ ) 
						vis[i+dx][j+dy] = true;
			}
		}
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) 
			if ( isalpha(bd[i][j]) ) {
				for ( int ii = 1; ii <= n; ii ++ )
					for ( int jj = 1; jj <= m; jj ++ )
						if ( !(i == ii && j == jj) && bd[i][j] == bd[ii][jj] )
							par[i][j] = mp(ii, jj);
			}
	memset(color, -1, sizeof(color));
	dfs(1, 0);
	printf("%d\n", tot*5040);
	for ( int i = 1; i <= n; i ++, puts("") )
		for ( int j = 1; j <= m; j ++ )
			if ( samp[i][j] == -1 ) printf(".");
			else printf("%d", samp[i][j]);
}
