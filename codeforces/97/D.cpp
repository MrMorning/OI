#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pair_t;

const int N_MAX = 1010;
const int offset[8][2] = {
	{0, 1}, {1, 0}, {0, -1}, {-1, 0},
	{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

int ans = 0, vis_idx = 0;
int w[N_MAX][N_MAX], vis[N_MAX][N_MAX];
vector<pair_t> vp;
int n, m;

void dfs( int tx, int ty, int mark ) {
	vis[tx][ty] = mark;
	for ( int dir = 0; dir < 4; dir ++ ) {
		int nx = tx + offset[dir][0],
			ny = ty + offset[dir][1];
			if ( 1 <= nx && nx <= n )
				if ( 1 <= ny && ny <= m ) {
					if ( w[nx][ny] == 1 && vis[nx][ny] == mark - 1 ) 
						dfs(nx, ny, mark);
				}
	}
}

void expand(int st_x, int st_y, int mark) {
	static pair_t Q[N_MAX * N_MAX];
	pair_t st = make_pair(st_x, st_y);
	vis[st_x][st_y] = mark;
	vp.clear();
	int qh = 0, qt = 0;
	Q[qt ++] = st;
	while ( qh < qt ) {
		pair_t now = Q[qh ++];
		for ( int dir = 0; dir < 8; dir ++ ) {
			pair_t next = make_pair(now.first + offset[dir][0], now.second + offset[dir][1]);
			int nx = next.first, ny = next.second;
			if ( 0 <= nx && nx <= n + 1)
				if ( 0 <= ny && ny <= m + 1) {
					if ( w[nx][ny] == 0 && !vis[nx][ny]) {
						vis[nx][ny] = true;
						Q[qt ++] = next;
					} 
					if ( w[nx][ny] == 1 && vis[nx][ny] != mark) {
						vis[nx][ny] = mark;
						vp.push_back(next);
					}
				}
		}
	}
	int sz = vp.size();
	if ( !sz ) return;
	for ( int i = 0; i < sz; i ++ ) 
		if ( vp[i].first == 0 || vp[i].first == n + 1
				|| vp[i].second == 0 || vp[i].second == m + 1 )
			return;
	for ( int i = 0; i < sz; i ++ ) {
		int tx = vp[i].first, ty = vp[i].second;
		int cnt = 0;
		for ( int dir = 0; dir < 4; dir ++ ) {
			int nx = tx + offset[dir][0],
				ny = ty + offset[dir][1];
			if ( 1 <= nx && nx <= n )
				if ( 1 <= ny && ny <= m )
					if ( w[nx][ny] == 1 && vis[nx][ny] == mark )
						cnt ++;
		}
		if ( cnt != 2 )
			return;
	}
	dfs(vp[0].first, vp[0].second, ++ vis_idx);
	for ( int i = 0; i < sz; i ++ ) {
		int tx = vp[i].first, ty = vp[i].second;
		if ( vis[tx][ty] != vis_idx )
			return;
	}
	ans = max(ans, sz);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char str[1111];
		scanf("%s", str);
		for ( int j = 1; j <= m; j ++ )
			w[i][j] = str[j - 1] - '0';
	}
	for ( int i = 0; i <= n + 1; i ++ )
		w[i][0] = w[i][m + 1] = 1;
	for ( int i = 0; i <= m + 1; i ++ )
		w[0][i] = w[n + 1][i] = 1;
	for ( int i = 1; i < n; i ++ )
		for ( int j = 1; j < m; j ++ )
			if ( w[i][j] == 1 && w[i][j + 1] == 1
					&& w[i + 1][j] == 1 && w[i + 1][j + 1] == 1 )
				ans = 4;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( w[i][j] == 0 && !vis[i][j] )
				expand(i, j, ++ vis_idx);
	printf("%d\n", ans);
}
