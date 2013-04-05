#include <cstdio>
typedef long long ll;
ll L, R;
int upper;
int count_sum(ll x) {
	int res = 0;
	while ( x )
		res += x % 10, x /= 10;
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%lld%lld%d", &L, &R, &upper);

	ll res = 0;
	for ( ll x = L; x <= R; x ++ ) {
		ll y = x, acc = 0;
		while ( 1 ) {
			acc += count_sum(y);
			if ( acc >= upper ) break;
			if ( y == R ) break;
			y ++;
		}
		if ( acc >= upper ) 
			res ++;
		x = y;
	}
	printf("%lld\n", res);
}
