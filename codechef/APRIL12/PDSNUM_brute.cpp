#include <cstdio>
typedef long long ll;
bool is_pds(int x) {
	ll sum = 0, prod = 1;
	while ( x ) {
		sum += x % 10, prod *= x % 10;
		x /= 10;
	}
	return prod % sum == 0;
}

bool has_zero(int x) {
	while ( x ) {
		if ( x % 10 == 0 )
			return true;
		x /= 10;
	}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	int N;

	while ( scanf("%d", &N), N ) {
		int cnt = 0, zero_cnt = 0;
		ll x;
		for ( x = 1; ; x ++ )
			if ( is_pds(x) ) {
				cnt ++;
				if ( has_zero(x) )
					zero_cnt ++;
				if ( cnt == N ) {
					printf("%lld\n", x);
					fprintf(stderr, "%d\n", zero_cnt);
					break;
				}
			}
	}
}
