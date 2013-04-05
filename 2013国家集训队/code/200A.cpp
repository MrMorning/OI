#include <cstdio>
#include <algorithm>
#define ABS(x) ((x)<0?-(x):(x))
using namespace std;
int n, m, k;
bool inv;

struct DSU {
	int ds[2005];
	void init(int n) {
		for ( int i = 0; i <= n+1; i ++ )
			ds[i] = i;
	}
	inline int find(int x) { return ds[x]==x?x:ds[x]=find(ds[x]); }
	inline void merge(int x, int y) { ds[x]=y; }
} toL[2005], toR[2005];

inline bool cmp(int x1, int y1, int x2, int y2, int x0, int y0) {
	int d1 = ABS(x1-x0)+ABS(y1-y0),
		d2 = ABS(x2-x0)+ABS(y2-y0);
	if ( d1 != d2 )
		return d1 < d2;
	if ( inv ) {
		if ( y1 != y2 )
			return y1 < y2;
		if ( x1 != x2 ) 
			return x1 < x2;
	} else {
		if ( x1 != x2 ) 
			return x1 < x2;
		if ( y1 != y2 )
			return y1 < y2;
	}
	return 0;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	if ( n > m ) {
		swap(n, m);
		inv = true;
	}
	for ( int i = 1; i <= n; i ++ )
		toL[i].init(m), toR[i].init(m);
	while ( k -- ) {
		int x, y;
		scanf("%d%d", &x, &y);
		if ( inv ) swap(x, y);

		int curV = 0x3f3f3f3f, curX = curV, curY = curV;
		for ( int d = 0; d <= curV; d ++ ) {
			if ( x-d >= 1 ) {
				int yl = toL[x-d].find(y),
					yr = toR[x-d].find(y);
				if ( yl != 0 && cmp(x-d, yl, curX, curY, x, y) )
					curV = d+ABS(y-yl), curX = x-d, curY = yl;
				if ( yr != m+1 && cmp(x-d, yr, curX, curY, x, y) )
					curV = d+ABS(y-yr), curX = x-d, curY = yr;
			}
			if ( x+d <= n ) {
				int yl = toL[x+d].find(y),
					yr = toR[x+d].find(y);
				if ( yl != 0 && cmp(x+d, yl, curX, curY, x, y) )
					curV = d+ABS(y-yl), curX = x+d, curY = yl;
				if ( yr != m+1 && cmp(x+d, yr, curX, curY, x, y) )
					curV = d+ABS(y-yr), curX = x+d, curY = yr;
			}
		}

		toL[curX].merge(curY, curY-1);
		toR[curX].merge(curY, curY+1);

		if ( inv ) swap(curX, curY);
		printf("%d %d\n", curX, curY);
	}
}
