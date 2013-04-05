#include <cstdio>
const int kWidthMax = 1010;
const int kEleMax = kWidthMax * kWidthMax;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int n, m;
bool done[kWidthMax][kWidthMax];
int cnt[kWidthMax][kWidthMax];
int ans = 0;
struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
	bool valid() {
		return 0 <= x && x < n && 0 <= y && y < m;
	}
	Point walk(int dir) {
		return Point(x + dx[dir], y + dy[dir]);
	}
} Q[kEleMax];
int main() {
	scanf("%d%d", &n, &m);
	int qh = 0, qt = 0;
	for ( int i = 0; i < n; i ++ ) {
		static char str[1111];
		scanf("%s", str);
		for ( int j = 0; j < m; j ++ ) 
			if ( str[j] == 'X' ) {
				Q[qt++] = Point(i, j);
				done[i][j] = true;
				ans ++;
			}
	}
	while ( qh != qt ) {
		Point u = Q[qh];
		qh = (qh + 1) % kEleMax;
		for ( int dir = 0; dir < 4; dir ++ ) {
			Point v = u.walk(dir);
			if ( v.valid() ) {
				cnt[v.x][v.y]++;
				if ( cnt[v.x][v.y] >= 2 && !done[v.x][v.y] ) {
					done[v.x][v.y] = true;
					ans ++;
					Q[qt] = v;
					qt = (qt + 1) % kEleMax;
				}
			}
		}
	}
	printf("%d\n", ans);
}
