#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int LEN_MAX = 1000000;
int seed;
bool is_prime(int x) {
	if ( x == 1 ) return false;
	for ( int t = 2; t <= (int)sqrt(x); t ++ )
		if ( x % t == 0 )
			return false;
	return true;
}
int P;
int haha() {
	return rand() % 2 == 0 ? rand() % (P - 1) + 1 : 0;
}
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	puts("1");
	for ( int t = 0; t < 1; t ++ ) {
		P = 10007;
		while ( !is_prime(P) )
			P = rand() % 10007 + 1;
		int Q = rand() % 10000 + 1;
		printf("%d %d %d %d %d %d %d %d\n", haha(), haha(), haha(), haha(), haha(), P, haha(), Q);
		while ( Q -- ) {
			ll l = (ll)rand() * rand() + 1,
			   r = (ll)rand() * rand() + 1;
			if ( r < l ) {
				r += l;
				l = r - l;
				r = r - l;
			}
			printf("%lld %lld\n", l, r);
		}
	}
}
