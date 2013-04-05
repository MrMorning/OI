#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int kNMax = 100010;
const double kEps = 1e-8;

struct Point {
	double x, y;
	void read() {
		int xx;
		scanf("%d", &xx);
		x= xx, y = 0;
	}
	bool operator< (const Point &T) const {
		return x < T.x;
	}
} p[kNMax], q;


double f(const Point &a, const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int n, k;
double ans = 1e100;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &k);
	k--;
	for ( int i = 0; i < n; i ++ )
		p[i].read();
	scanf("%lf%lf", &q.x, &q.y);
	double tmp = p[k].x;
	sort(p, p + n);
	if ( k != n )
		for ( int i = 0; i < n; i ++ )
			if ( fabs(p[i].x-tmp) < kEps ) k = i;
	if ( k == n ) {
		ans = min(f(q, p[0]), f(q, p[n-1])) + f(p[0], p[n-1]);
	} else {
		for ( int i = 0; i < n; i ++ ) {
			if ( 0 <= k && k <= i ) 
				ans = min(ans, min(f(p[k], p[0])+f(p[0], p[i])+f(q, p[i]),f(p[k], p[i])+f(p[i], p[0])+f(p[0], q)) 
						+ (i==n-1?0:min(f(q, p[i+1])+f(p[i+1],p[n-1]), f(q, p[n-1])+f(p[n-1],p[i+1]))));
			if ( i <= k && k < n )
				ans = min(ans, min(f(p[k], p[n-1])+f(p[n-1], p[i])+f(q, p[i]),f(p[k], p[i])+f(p[i], p[n-1])+f(p[n-1], q)) 
						+ (i==0?0:min(f(q, p[i-1])+f(p[i-1],p[0]), f(q, p[0])+f(p[0],p[i-1]))));
		}
	}
	printf("%.10lf\n", ans);
}
