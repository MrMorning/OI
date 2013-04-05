#include <cstdio>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff - 1;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int nRow, nCol;
int calcDist(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) + abs(y2 - y1);
}
int judge(int d) {
	if ( d % 2 == 0 ) return (d - 1) * 2;
	else return (d - 1) * 2 + 1;
}
int solve(int x1, int y1, int x2, int y2) {
	//x1,y1:cop; x2,y2:thief

	if ( x1 == x2 && y1 == y2 )
		return 0;

	if ( nRow == 1 || nCol == 1 ) {
		if ( nRow == 1 ) {
			if ( y1 < y2 ) 
				return 2 * (nCol - y2) + judge(y2 - y1);
			else
				return 2 * (y2 - 1) + judge(y1 - y2);
		} else {
			if ( x1 < x2 )
				return 2 * (nRow - x2) + judge(x2 - x1);
			else
				return 2 * (x2 - 1) + judge(x1 - x2);
		}
	} 
	int dist = calcDist(x1, y1, x2, y2);
	if ( dist & 1 )
		return inf;
	int ans = 0;
	if ( calcDist(1, 1, x2, y2) < calcDist(1, 1, x1, y1) ) {
		//topleft
		ans = max(ans, 2 * (calcDist(1, 1, x1, y1) - 1));
	}
	if ( calcDist(1, nCol, x2, y2) < calcDist(1, nCol, x1, y1) ) {
		//topright
		ans = max(ans, 2 * (calcDist(1, nCol, x1, y1) - 1));
	}
	if ( calcDist(nRow, 1, x2, y2) < calcDist(nRow, 1, x1, y1) ) {
		//bottomleft
		ans = max(ans, 2 * (calcDist(nRow, 1, x1, y1) - 1));
	}
	if ( calcDist(nRow, nCol, x2, y2) < calcDist(nRow, nCol, x1, y1) ) {
		//bottomright
		ans = max(ans, 2 * (calcDist(nRow, nCol, x1, y1) - 1));
	}
	return ans;
}
int main() {
	int x1, y1, x2, y2;
	char ord[5];
	scanf("%d%d", &nRow, &nCol);
	scanf("%d%d", &x1, &y1);
	scanf("%d%d", &x2, &y2);
	scanf("%s", ord);
	if ( ord[0] == 'C' ) {
		int ans = inf;
		for ( int dir = 0; dir < 4; dir ++ ) {
			int nx1 = x1 + dx[dir],
				ny1 = y1 + dy[dir];
			if ( 1 <= nx1 && nx1 <= nRow
					&& 1 <= ny1 && ny1 <= nCol )
				ans = min(ans, solve(nx1, ny1, x2, y2) + 1);
		}
		printf("%d\n", ans == inf ? 0 : ans);
	} else {
		int ans = solve(x1, y1, x2, y2);
		printf("%d\n", ans == inf ? 0 : ans);
	}
}
