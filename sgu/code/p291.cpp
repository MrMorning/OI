#include <cstdio>
const int N_MAX = 30000;
const int Q_MAX = 1005;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
struct Element {
	int x, y, col, step;
	Element(){}
	Element(int _x, int _y, int _col, int _step):
		x(_x), y(_y), col(_col), step(_step){}
} que[Q_MAX * Q_MAX];
int color[Q_MAX][Q_MAX];
int ans[N_MAX];
int q, c, n, t;
int main() {
	scanf("%d%d%d%d", &q, &c, &n, &t);
	int qt = 0;
	for ( int i = 1; i <= n; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		que[qt ++] = Element(x, y, i, 0);
		color[x][y] = i;
	}
	for ( int qh = 0; qh < qt; qh ++ ) {
		Element top = que[qh];
		if ( top.step == t )
			continue;
		for ( int dir = 0; dir < 4; dir ++ ) {
			int tx = top.x + dx[dir],
				ty = top.y + dy[dir];
			if ( 1 <= tx && tx <= q )
				if ( 1 <= ty && ty <= c ) 
					if ( !color[tx][ty] ) {
						color[tx][ty] = top.col;
						que[qt ++] = Element(tx, ty, top.col, top.step + 1);
					}
		}
	}
	for ( int i = 1; i <= q; i ++ )
		for ( int j = 1; j <= c; j ++ )
			if ( color[i][j] )
				ans[color[i][j]] ++;
	for ( int i = 1; i <= n; i ++ )
		printf("%d\n", ans[i]);
}
