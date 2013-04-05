
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
	Point walk(int dir) {
		return Point(x + dx[dir], y + dy[dir]);
	}
} Q[4510*4510];
int n, m;
char board[1510][1510];
bool obs[4510][4510];

bool vis[4510][4510];

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int sx, sy;
	for ( int i = 0; i < n; i ++ ) {
		scanf("%s", board[i]);
		for ( int j = 0; j < m; j ++ ) {
			obs[i][j] = board[i][j] == '#';
			if ( board[i][j] == 'S' ) 
				sx = i, sy = j;
		}
	}
	int qt = 0;
	Q[qt++] = Point(n + sx, m + sy);
	vis[n+sx][m+sy] = true;
	for ( int qh = 0; qh < qt; qh ++ ) {
		Point u = Q[qh];
		for ( int dir = 0; dir < 4; dir ++ ) {
			Point v = u.walk(dir);
			if ( 0 <= v.x && v.x < 3 * n )
				if ( 0 <= v.y && v.y < 3 * m )
					if ( !vis[v.x][v.y] && !obs[v.x%n][v.y%m]) {
						vis[v.x][v.y] = true;
						Q[qt++] = v;
					}
		}
	}
	for ( int kx = 0; kx < 3; kx ++ )
		for ( int ky = 0; ky < 3; ky ++ )
			if ( !(kx == 1 && ky == 1) ) {
				if ( vis[kx*n+sx][ky*m+sy] ) {
					puts("Yes");
					return 0;
				}
			}
	puts("No");
}
