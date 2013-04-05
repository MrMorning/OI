#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int N_MAX = 20010;
ll x[N_MAX], y[N_MAX];
int n;
bool inside(ll x0, ll y0, ll d, int i) {
	return x[i] >= x0 && x[i] <= x0 + d 
		&& y[i] >= y0 && y[i] <= y0 + d;
}
bool test1(ll x0, ll y0, ll x1, ll y1, ll d) {
	static bool cover[N_MAX];
	memset(cover, 0, sizeof(cover));
	for ( int i = 0; i < n; i ++ )
		cover[i] = inside(x0, y0, d, i) || inside(x1, y1, d, i);
	ll xMax = -inf, xMin = inf;
	ll yMax = -inf, yMin = inf;
	for ( int i = 0; i < n; i ++ )
		if ( !cover[i] ) {
			xMax = max(x[i], xMax);
			xMin = min(x[i], xMin);
			yMax = max(y[i], yMax);
			yMin = min(y[i], yMin);
		}
	return xMax - xMin <= d && yMax - yMin <= d;
}

bool test2(ll x0, ll y0, ll x1, ll y1, ll d) {
	static bool cover[N_MAX];
	memset(cover, 0, sizeof(cover));
	for ( int i = 0; i < n; i ++ )
		cover[i] = inside(x0, y0, d, i);
	ll xMin = inf;
	ll yMin = inf;
	for ( int i = 0; i < n; i ++ )
		if ( !cover[i] ) {
			if ( x[i] < x1 && y[i] < y1 )
				return false;
			if ( x[i] >= x1 ) 
				yMin = min(yMin, y[i]);
			if ( y[i] >= y1 )
				xMin = min(xMin, x[i]);
		}
	for ( int i = 0; i < n; i ++ )
		if ( !cover[i] )
			if ( !inside(xMin, y1, d, i) && !inside(x1, yMin, d, i) )
				return false;
	return true;
}

bool check(ll d) {
	for ( int rot = 0; rot < 4; rot ++ ) {
		ll xMax = -inf, xMin = inf;
		ll yMax = -inf, yMin = inf;
		for ( int i = 0; i < n; i ++ ) {
			xMax = max(x[i], xMax);
			xMin = min(x[i], xMin);
			yMax = max(y[i], yMax);
			yMin = min(y[i], yMin);
		}
		if ( test1(xMin, yMin, xMax - d, yMax - d, d) )
			return true;
				if ( test2(xMin, yMin, xMax - d, yMax - d, d) )
					return true;

		//rotate 90 degrees
		for ( int i = 0; i < n; i ++ ) {
			ll xt = x[i], yt = y[i];
			x[i] = yt, y[i] = -xt;
		}
	}
	return false;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) 
		scanf(LL_FMT LL_FMT, &x[i], &y[i]);
	check(1);
	ll lb = 0, rb = 2000000000; 
	for ( ll mid = (lb + rb) / 2;
			lb < rb - 1; mid = (lb + rb) / 2) {
		if ( check(mid) )
			rb = mid;
		else
			lb = mid;
	}
	printf(LL_FMT, rb);
}
