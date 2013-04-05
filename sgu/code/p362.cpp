#include <cstdio>
int n, m, x, y;
bool vis[11][11];
bool valid(int x, int y) {
	return 1 <= x && x <= n
		&& 1 <= y && y <= m;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &x, &y);
	while ( 1 ) {
		vis[x][y] = true;
		if ( valid(x + 1, y) && !vis[x + 1][y] ) {
			printf("D");
			x ++;
			continue;
		}
		if ( valid(x, y - 1) && !vis[x][y - 1] ) {
			printf("L");
			y --;
			continue;
		}
		if ( valid(x - 1, y) && !vis[x - 1][y] ) {
			printf("U");
			x --;
			continue;
		}
		if ( valid(x, y + 1) && !vis[x][y + 1] ) {
			printf("R");
			y ++;
			continue;
		}
		break;
	}
}
