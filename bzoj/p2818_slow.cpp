#include <cstdio>
typedef long long ll;
const int kNMax = 10000010;
int n;
bool notPrime[kNMax];
int prime[kNMax], mu[kNMax];
int primeCnt = 0;

void prework() {
	mu[1] = 1;
	for ( int x = 2; x <= n; x ++ ) {
		if ( !notPrime[x] ) {
			prime[primeCnt++] = x;
			mu[x] = -1;
		}
		for ( int i = 0; i < primeCnt && prime[i] * x <= n; i ++ ) {
			int y = prime[i] * x;
			notPrime[y] = true;
			mu[y] = mu[x] * -1;
			if ( x % prime[i] == 0 )
				mu[y] = 0;
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	prework();
	ll ans = 0;
	for ( int i = 0; i < primeCnt; i ++ ) {
		int p = prime[i];
		for ( int d = 1; d <= n / p; d ++ )
			ans += (ll)(n / (p*d)) * (n / (p*d)) * mu[d];
	}
	printf("%lld\n", ans);
}
