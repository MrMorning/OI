#include <cstdio>
typedef long long ll;

ll bino(int n, int k) {
	ll ret = 1;
	for ( int i = 1; i <= k; i ++ )
		ret = ret * (n - i + 1) / i;
	return ret;
}

bool check(int n, int m, int x) {
	ll ret = 0;
	for ( int i = 0; ret <= (ll)m * x && i <= x; i ++ ) {
		if ( n <= bino(x, i) ) {
			ret += (ll)n * i;
			n = 0;
			break;
		} else {
			n -= bino(x, i);
			ret += bino(x, i) * i;
		}
	}
	if ( n > 0 ) return false;
	return ret <= (ll)m * x;
}

int solve(int n, int m) {
	int lb = 0, rb = n - 1;
	for ( int mid = (lb + rb) / 2; lb < rb - 1;
			mid = (lb + rb) / 2 ) {
		if ( check(n, m, mid) )
			rb = mid;
		else
			lb = mid;
	}
	return rb;
}

int main() {
//	freopen("t.in", "r", stdin);
	int tst;
	scanf("%d", &tst);
	while ( tst -- ) {
		int n, m;
		scanf("%d%d", &n, &m);
		if ( m > n / 2 )
			m = n / 2;
		printf("%d\n", solve(n, m));
	}
}
