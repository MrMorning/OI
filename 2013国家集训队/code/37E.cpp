#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

const int inf = 0x3f3f3f3f;
const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m;
int color[55][55];

int solve(int st_x, int st_y) {
	static int dist[55][55];
	static pair<int, int> Q[55*55];
	memset(dist, -1, sizeof(dist));
	int qh = 0, qt = 0;
	Q[qt ++] = make_pair(st_x, st_y);
	int cur_dist = dist[st_x][st_y] = 0;
	int cur_color = color[st_x][st_y];

	while ( qh < qt ) {

		for ( int i = qh; i < qt; i ++ ) {
			pair<int, int> u = Q[i];
			for ( int d = 0; d < 4; d ++ ) {
				pair<int, int> v = 
					make_pair(u.first + offset[d][0],
							u.second + offset[d][1]);
				if ( 1 <= v.first && v.first <= n )
					if ( 1 <= v.second && v.second <= m ) 
						if ( dist[v.first][v.second] == -1 )
							if ( color[v.first][v.second] == cur_color ) {
								Q[qt ++] = v;
								dist[v.first][v.second] = cur_dist;
							}
			}
		}

		int lim = qt;
		for ( int i = qh; i < lim; i ++ ) {
			pair<int, int> u = Q[i];
			for ( int d = 0; d < 4; d ++ ) {
				pair<int, int> v = 
					make_pair(u.first + offset[d][0],
							u.second + offset[d][1]);
				if ( 1 <= v.first && v.first <= n )
					if ( 1 <= v.second && v.second <= m ) 
						if ( dist[v.first][v.second] == -1 ) {
							assert(color[v.first][v.second] == !cur_color);
							Q[qt ++] = v;
							dist[v.first][v.second] = cur_dist + 1;
						}
			}
		}
		if ( lim == qt )
			break;
		qh = lim;
		cur_dist ++;
		cur_color ^= 1;
	}
	return cur_dist + (cur_color == 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char str[55];
		scanf("%s", str + 1);
		for ( int j = 1; j <= m; j ++ )
			color[i][j] = str[j] == 'B';
	}
	int ans = inf;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			ans = min(ans, solve(i, j));
	printf("%d\n", ans);
}
