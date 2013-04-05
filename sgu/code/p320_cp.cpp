#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const int WIDTH = 555;

#define DOWN 0
#define UP 1
#define LEFT 2
#define RIGHT 3


int n, m, bound;
int belong[WIDTH][WIDTH];
char board[WIDTH][WIDTH];
int colIdx = 0;
int weight[WIDTH * WIDTH];
bool flooded[WIDTH][WIDTH];

struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):x(_x), y(_y){}
	bool valid() {
		return 0 <= x && x < n && 0 <= y && y < m;
	}
	Point walk(int dir) {
		return Point(x + dx[dir], y + dy[dir]);
	}
};

void color(int sx, int sy, int col) {
	static Point Q[WIDTH * WIDTH];
	int qt = 0;
	belong[sx][sy] = col;
	Q[qt ++] = Point(sx, sy);
	for ( int qh = 0; qh < qt; qh ++ ) {
		Point u = Q[qh];
		for ( int dir = 0; dir < 4; dir ++ ) {
			Point v = u.walk(dir);
			if ( v.valid() && belong[v.x][v.y] == -1 && board[v.x][v.y] == board[u.x][u.y]) {
				belong[v.x][v.y] = col;
				Q[qt ++] = v;
			}
		}
	}
}

int getBel(int x, int y) {
	if ( x < 0 || x > n || y < 0 || y > m )
		return -1;
	return belong[x][y];
}

bool blocked(int x1, int y1, int x2, int y2) {
	if ( getBel(x1, y1) != getBel(x2, y2) )
		return false;
	if ( getBel(x1, y1) == -1 )
		return false;
	if ( weight[belong[x1][y1]] < bound )
		return false;
	return true;
}

bool canflow(Point u, int dir) {
	Point v = u.walk(dir);
	if ( 0 <= v.x && v.x <= n )
		if ( 0 <= v.y && v.y <= m ) {
			if ( dir == DOWN ) {
				return !(blocked(u.x, u.y - 1, u.x, u.y) 
						|| blocked(u.x, u.y - 1, u.x - 1, u.y)
						|| blocked(u.x, u.y, u.x - 1, u.y - 1));
			} else if ( dir == UP ) {
				return !(blocked(u.x - 1, u.y, u.x - 1, u.y - 1) 
						|| blocked(u.x, u.y, u.x - 1, u.y - 1)
						|| blocked(u.x, u.y - 1, u.x - 1, u.y));
			} else if ( dir == LEFT ) {
				return !(blocked(u.x, u.y - 1, u.x - 1, u.y - 1) 
						|| blocked(u.x, u.y, u.x - 1, u.y - 1)
						|| blocked(u.x, u.y - 1, u.x - 1, u.y));
			} else {
				return !(blocked(u.x, u.y, u.x - 1, u.y) 
						|| blocked(u.x, u.y, u.x - 1, u.y - 1)
						|| blocked(u.x, u.y - 1, u.x - 1, u.y));
			}
		}
	return false;
}

void floodfill() {
	static Point Q[WIDTH * WIDTH];
	int qt = 0;
	flooded[0][0] = true;
	Q[qt ++] = Point(0, 0);
	for ( int qh = 0; qh < qt; qh ++ ) {
		Point u = Q[qh];

		for ( int dir = 0; dir < 4; dir ++ ) 
			if ( canflow(u, dir) ) {
				Point v = u.walk(dir);
				if ( !flooded[v.x][v.y] ) {
					flooded[v.x][v.y] = true;
					Q[qt++] = v;
				}
			}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &bound);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%s", board[i]);
	memset(belong, -1, sizeof(belong));
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ ) 
			if ( belong[i][j] == -1 ) 
				color(i, j, colIdx++);
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ ) 
			weight[belong[i][j]] ++;
	floodfill();
	int ans = 0;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			if ( weight[belong[i][j]] >= bound ) 
				ans ++;
			else {
				if ( !(flooded[i][j] && flooded[i + 1][j] && flooded[i][j + 1] && flooded[i + 1][j + 1]) )
					ans ++;
			}
	printf("%d\n", ans);
//	printf("%d\n", canflow(Point(0,1), DOWN));
}
