#include <cstdio>
typedef long long ll;
const int kNMax = 10000010;
int n;
bool notPrime[kNMax];
int prime[kNMax], mu[kNMax];
ll f[kNMax];
int primeCnt = 0;

void prework() {
	mu[1] = 1;
	f[1] = 0;
	for ( int x = 2; x <= n; x ++ ) {
		if ( !notPrime[x] ) {
			prime[primeCnt++] = x;
			mu[x] = -1;
			f[x] = 1;
		}
		for ( int i = 0; i < primeCnt && prime[i] * x <= n; i ++ ) {
			int y = prime[i] * x;
			notPrime[y] = true;
			if ( x % prime[i] == 0 ) {
				mu[y] = 0;
				f[y] = mu[x];
			} else {
				mu[y] = mu[x] * -1;
				f[y] = f[x] * -1 + mu[x];
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	prework();
	ll ans = 0;
	for ( int t = 1; t <= n; t ++ )
		ans += (ll)(n / t) * (n / t) * f[t]; 
	printf("%lld\n", ans);
}
