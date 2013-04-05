#include <cstdio>
#include <algorithm>
using namespace std;
const int kDx[24] = {0, 0, 1, -1, -2, -1, -1, 0, 0, 1, 1, 2, -3. -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 3};
const int kDy[24] = {1, -1, 0, 0, 0, -1, 1, -2, 2, -1, 1, 0, 0, -1, 1, -2, 2, 3, -3, -2, 2, -1, 1, 0};
const int kDz[24] = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
int n, m, k;
bool vis[2005][2005];
int memo[2005][2005][3];

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			memo[i][j][0] = i;
			memo[i][j][1] = j;
			memo[i][j][2] = 0;
		}
	while ( k -- ) {
		int x, y;
		scanf("%d%d", &x, &y);
		register int &x0 = memo[x][y][0], &y0 = memo[x][y][1], &dist = memo[x][y][2];
		int best = 0;
		for ( int dir = 0; dir < 12; dir ++ ) {
			int xx = x + kDx[dir], yy = y + kDy[dir];
			if ( 1 <= xx && xx <= n && 1 <= yy && yy <= m )
				best = max(best, memo[xx][yy][2]-kDz[dir]);
		}
		if ( best > dist ) 
			dist = best, y0 = y, x0 = x-dist;
		while ( !(1 <= x0 && x0 <= n && 1 <= y0 && y0 <= m && !vis[x0][y0]) ) {
			if ( y0 == y ) {
				if ( x0 >= x ) {
					dist++;
					x0 = x-dist;
				} else {
					x0++; y0--;
				}
			} else {
				if ( y0 < y ) 
					y0 = y+y-y0;
				else {
					if ( x0 < x )
						y0 = y+y-y0-1;
					else
						y0 = y+y-y0+1;
					x0++;
				}
			}
		}
		vis[x0][y0] = true;
		printf("%d %d\n", x0, y0);
	}
}
