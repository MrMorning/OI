#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const int kVMax = 1000000;

bool notprime[kVMax+1];
int mu[kVMax+1], prime[kVMax+1], primeCnt;

void prework() {
	mu[1] = 1;
	for ( int x = 2; x <= kVMax; x ++ ) {
		if ( !notprime[x] ) {
			prime[primeCnt++] = x;
			mu[x] = -1;
		}
		for ( int i = 0; i < primeCnt && prime[i] <= kVMax / x; i ++ ) {
			int y = prime[i] * x;
			notprime[y] = true;
			if ( x % prime[i] == 0 ) {
				mu[y] = 0;
				break;
			} else
				mu[y] = mu[x] * -1;
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	prework();
	int n, m;
	scanf("%d%d", &n, &m);
	if ( n == 1 && m == 1 ) puts("0");
	else if ( n == 1 || m == 1 ) puts("1");
	else {	
		n--, m--;
		ll ans = 2;
		for ( int i = 1; i <= min(n, m); i ++ )
			ans += (ll)mu[i]*(n/i)*(m/i);
		printf(LL_FMT "\n", ans);
	}
}
