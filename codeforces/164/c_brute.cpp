#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool isSqr[20001];

int sqr(int x) { return x*x; }

struct Point {
	int x, y;
	Point(){}
	Point(int xx, int yy):
		x(xx), y(yy){}
} arr[10010], ansMem[10010], chose[10010];
int nArr;
int ansBest = 0;

bool isIntDist(const Point &p1, const Point &p2) {
	return isSqr[sqr(p1.x-p2.x)+sqr(p1.y-p2.y)];
}

void sweep(const Point &p) {
	for ( int i = 0; i < nArr; i ++ ) {
		if ( isIntDist(arr[i], p) ) {
			swap(arr[i], arr[nArr-1]);
			nArr--;
			i--;
		}
	}
}

void dfs(int i) {
	if ( i+nArr < ansBest ) return;
	if ( i > ansBest ) {
		ansBest = i;
		memcpy(ansMem, chose, sizeof(ansMem));
	}
	for ( int k = 0; k < nArr; k ++ ) {
		chose[i] = arr[k];
		sweep(chose[i]);
		dfs(i+1);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	for ( int x = 0; x*x <= 20000; x ++ )
		isSqr[x*x] = true;
	int n, m;
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			chose[0] = Point(i, 0);
			chose[1] = Point(0, j);
			nArr = 0;
			for ( int x = 0; x <= n; x ++ )
				for ( int y = 0; y <= m; y ++ )
					if ( x != 0 || y != 0 )
						arr[nArr++] = Point(x, y);
			sweep(chose[0]);
			sweep(chose[1]);
			dfs(2);
		}
	printf("%d\n", ansBest);
	for ( int i = 0; i < ansBest; i ++ )
		printf("%d %d\n", ansMem[i].x, ansMem[i].y);
}
