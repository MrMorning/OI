#include <cstdio>
#include <algorithm>
using namespace std;
inline int sgn(int x) {
	if ( x == 0 ) return 0;
	if ( x < 0 ) return -1;
	return 1;
}
struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
	bool operator== (const Point &t) const {
		return x == t.x && y == t.y;
	}
} p[4010];

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

int getDist(const Point &p1, const Point &p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

bool isItc(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	return sgn(cross(q1 - p2, p1 - p2)) * sgn(cross(p1 - p2, q2 - p2)) >= 0
		&& sgn(cross(p1 - q2, q1 - q2)) * sgn(cross(q1 - q2, p2 - q2)) >= 0;
}

bool onLine(const Point &p, const Point &q1, const Point &q2) {
	if ( q1.x == q2.x )
		return p.y >= min(q1.y, q2.y) && p.y <= max(q1.y, q2.y);
	else
		return p.x >= min(q1.x, q2.x) && p.x <= max(q1.x, q2.x);
}

int n;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d%d", &p[i].x, &p[i].y);
	int ans, cur = 0;
	for ( int i = 0; i < min(n - 1, 3); i ++ )
		cur += getDist(p[i], p[i + 1]);
	if ( n <= 3 ) {
		printf("%d\n", cur);
		return 0;
	}
	ans = cur;
	for ( int i = 4, pre = 0; i < n; i ++ ) {
		cur += getDist(p[i], p[i - 1]);
		int j;
		for ( j = i - 3; j >= pre; j -- ) 
			if ( isItc(p[j], p[j + 1], p[i - 1], p[i]) )
				break;
		if ( j != pre - 1 ) {
			for ( int k = pre; k <= j; k ++ )
				cur -= getDist(p[k], p[k + 1]);
			if ( p[i].x == p[i - 1].x )
				ans = max(ans, cur + abs(p[i].x - p[j + 1].x) - abs(p[j].y - p[i].y));
			else
				ans = max(ans, cur + abs(p[j + 1].y - p[i].y) - abs(p[j].x - p[i].x));
			pre = j + 1;
		}
		ans = max(ans, cur);
	}
	printf("%d\n", ans);
}
