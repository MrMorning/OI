#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
int sgn(ll x) {
	if ( x == 0 ) return 0;
	return x > 0 ? 1 : -1;
}
void nosol() {
	puts("0");
	exit(0);
}

struct Point {
	int x, y;
	Point(){}
	Point(int xx, int yy): x(xx), y(yy){}
} p[1010];
int n;
int arr[1000010];

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x,p1.y-p2.y);
}

ll cross(const Point &p1, const Point &p2) {
	return (ll)p1.x * p2.y - (ll)p1.y * p2.x;
}

double getX(Point p1, Point p2) {
	Point v = p2-p1;
	double k = (double)(p[0].y-p1.y)/v.y;
	return p1.x+k*v.x;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d%d", &p[i].x, &p[i].y);
	if ( p[2].y > p[1].y ) {
		for ( int k = 0; k < n; k ++ )
			p[k].y = p[1].y*2-p[k].y;
		for ( int k = 2; k <= n/2; k ++ )
			swap(p[k], p[n+1-k]);
		swap(p[0], p[1]);
	}
	p[n] = p[0];
	int convCnt = 0;
	for ( int i = 2; i <= n-1; i++ ) {
		if ( cross(p[i-1]-p[i], p[i+1]-p[i]) >= 0 ) {
			convCnt++;
			int lb, rb;
			ll tmp1 = cross(p[i+1]-p[i], p[0]-p[i]),
			   tmp2 = cross(p[i+1]-p[i], p[1]-p[i]);
			if ( tmp1 >= 0 && tmp2 <= 0 )
				lb = (int)ceil(getX(p[i+1], p[i]));
			else if ( (tmp1 <= 0 && tmp2 >= 0) || (tmp1 <= 0 && tmp2 <= 0) )
				lb = p[0].x;
			else
				nosol();

			tmp1 = cross(p[i-1]-p[i], p[0]-p[i]);
			tmp2 = cross(p[i-1]-p[i], p[1]-p[i]);

			if ( tmp1 >= 0 && tmp2 <= 0 )
				rb = (int)floor(getX(p[i-1], p[i]));
			else if ( (tmp1 >= 0 && tmp2 >= 0) || (tmp1 <= 0 && tmp2 >= 0) )
				rb = p[1].x;
			else
				nosol();

			assert(lb <= rb);
			//fprintf(stderr, "[%d, %d]\n", lb, rb);
			arr[lb]++; arr[rb+1]--;
		}	
	}
	int val = 0, ans = 0;
	for ( int i = p[0].x; i <= p[1].x; i ++ ) {
		val += arr[i];
		if ( val == convCnt ) ans ++;
	}
	printf("%d\n", ans);
}
