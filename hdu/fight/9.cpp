#include <cstdio>
#include <cmath>

int gcd(int a, int b) {
	return b ? a : gcd(b, a % b);
}

int calc(int x) {
	int res = 0;
	for ( int y = 2, lim = (int)sqrt(x); y <= lim; y ++ )
		if ( x != y && x % y == 0 ) {
			int cnt = 0;
			while ( x % y == 0 ) {
				cnt ++;
				x /= y;
			}
			if ( res == 0 )
				res = cnt;
			else
				res = gcd(res, cnt);
		}
	if ( x > 1 )
		res = 1;
	if ( res == 0 )
		res = 1;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	int acc = 0;
	for ( int i = 1; i <= n; i ++ ) {
		if ( calc(i) > 1 )
		printf("%d %d\n", i, calc(i));

	}
}
