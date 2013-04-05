#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

const int offset[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
const int LENGTH = 2048;

struct IndexTree {
	int ele[LENGTH + 1][LENGTH + 1];
	int sum(int x, int y) {
		int res = 0;
		for ( int i = x; i; i -= i & -i )
			for ( int j = y; j; j -= j & -j )
				res += ele[i][j];
		return res;
	}
	int sum(int x1, int y1, int x2, int y2) {
		if ( x1 > x2 || y1 > y2 )
			return 0;
		int res = sum(x2, y2);
		if ( x1 > 1 )
			res -= sum(x1 - 1, y2);
		if ( y1 > 1 )
			res -= sum(x2, y1 - 1);
		if ( x1 > 1 && y1 > 1 )
			res += sum(x1 - 1, y1 - 1);
		return res;
	}
	void add(int x, int y, int val) {
		for ( int i = x; i <= LENGTH; i += i & -i )
			for ( int j = y; j <= LENGTH; j += j & -j )
				ele[i][j] += val;
	}
} idt0, idtX, idtY, idtXY, idtt;

void appendChange(int x, int y, int delta) {
	idt0.add(x, y, delta);
	idtX.add(x, y, x * delta);
	idtY.add(x, y, y * delta);
	idtXY.add(x, y, x * y * delta);
}

int calcSum(int x, int y) {
	int res = 0;
	res += x * y * idt0.sum(x + 1, y + 1, LENGTH, LENGTH);
	res += x * idtY.sum(x + 1, 1, LENGTH, y);
	res += y * idtX.sum(1, y + 1, x, LENGTH);
	res += idtXY.sum(x, y);
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	static char cmd[10];
	scanf("X %d %d", &n, &m);
	while ( scanf("%s", cmd) != EOF ) {
		if ( cmd[0] != 'L' && cmd[0] != 'k' )
			break;
		if ( cmd[0] == 'L' ) {
			int x1, y1, x2, y2, delta;
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &delta);
			appendChange(x2, y2, delta);
			if ( y1 > 1 )
				appendChange(x2, y1 - 1, -delta);
			if ( x1 > 1 )
				appendChange(x1 - 1, y2, -delta);
			if ( x1 > 1 && y1 > 1 )
				appendChange(x1 - 1, y1 - 1, delta);
		} else {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			int res = calcSum(x2, y2);
			if ( y1 > 1 )
				res -= calcSum(x2, y1 - 1);
			if ( x1 > 1 )
				res -= calcSum(x1 - 1, y2);
			if ( x1 > 1 && y1 > 1 )
				res += calcSum(x1 - 1, y1 - 1);
			printf("%d\n", res);
		}
	}
}
