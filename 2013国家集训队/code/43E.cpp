#include <cstdio>
#include <cassert>
typedef long long ll;
struct Segment {
	int v, t, s;
} seg[111][111];
int nSeg[111];
int ans = 0;
int sgn(ll x) {
	if ( x == 0 ) return 0;
	return x > 0 ? 1 : -1;
}
struct Point {
	int x, y;
	Point(int _x, int _y):
		x(_x), y(_y){}
};
Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}
ll cross(const Point &p1, const Point &p2) {
	return (ll)p1.x * p2.y - (ll)p1.y * p2.x;
}
bool isIntersected(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	return sgn(cross(q1-p1, p2-p1)) * sgn(cross(p2-p1, q2-p1)) > 0 
		&& sgn(cross(p1-q1, q2-q1)) * sgn(cross(q2-q1, p2-q1)) > 0;
}
int main() {
//	freopen("t.in", "r", stdin);
	int n, tots;
	scanf("%d%d", &n, &tots);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d", &nSeg[i]);
		for ( int j = 0; j < nSeg[i]; j ++ ) {
			scanf("%d%d", &seg[i][j].v, &seg[i][j].t);
			seg[i][j].s = seg[i][j].v * seg[i][j].t;
		}
	}
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < i; j ++ ) {
			int pi = 0, pj = 0;
			int si = 0, sj = 0;
			int ti = 0, tj = 0;
			while ( 1 ) {
				if ( ti + seg[i][pi].t > tj + seg[j][pj].t ) {
					if ( pj == nSeg[j] - 1 ) break;
					tj += seg[j][pj].t;
					sj += seg[j][pj].s;
					pj++;
				} else { 
					if ( pi == nSeg[i] - 1 ) break;
					ti += seg[i][pi].t;
					si += seg[i][pi].s;
					pi++;
				}
				if ( isIntersected(Point(ti, si), Point(ti + seg[i][pi].t, si + seg[i][pi].s),
							Point(tj, sj), Point(tj + seg[j][pj].t, sj + seg[j][pj].s)) )
					ans ++;
				if ( si == sj && ti == tj ) {
					assert(pi >= 1 && pj >= 1);
					if ((seg[i][pi-1].v-seg[j][pj-1].v) * (seg[i][pi].v-seg[j][pj].v) > 0)
						ans++;
				} 
				if ( tj < ti && ti < tj + seg[j][pj].t 
						&& (ti-tj)*seg[j][pj].v+sj == si ) {
					assert(pi > 0);
					ans += (seg[j][pj].v-seg[i][pi].v)*(seg[j][pj].v-seg[i][pi-1].v) > 0;
				} 
				if ( ti < tj && tj < ti + seg[i][pi].t
						&& (tj-ti)*seg[i][pi].v+si == sj ) {
					assert(pj > 0);
					ans += (seg[i][pi].v-seg[j][pj].v)*(seg[i][pi].v-seg[j][pj-1].v) > 0;
				}

			}
		}
	printf("%d\n", ans);
}
