#include <cstdio>
int n;
bool vis[1111][1111];
bool inrange(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}
bool check(int x, int y) {
	bool ret = true;
	for ( int dx = 0; dx <= 2; dx ++ )
		for ( int dy = 0; dy <= 2; dy ++ )
			ret &= inrange(x+dx, y+dy) && vis[x+dx][y+dy];
	return ret;
}
int m;
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	if ( n < 3 ) {
		printf("-1\n");
		return 0;
	}
	for ( int i = 1; i <= m; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		vis[x][y] = true;
		for ( int dx = -2; dx <= 0; dx ++ )
			for ( int dy = -2; dy <= 0; dy ++ )
				if ( check(x + dx, y + dy) ) {
					printf("%d\n", i);
					return 0;
				}
	}
	printf("-1\n");
}
