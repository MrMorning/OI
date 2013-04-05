#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 10000010;
bool notPrime[kNMax];
int prime[kNMax], mu[kNMax];
ll f[kNMax], sumf[kNMax];
int primeCnt = 0;

void prework() {
	mu[1] = 1;
	f[1] = 0;
	for ( int x = 2; x <= kNMax-1; x ++ ) {
		if ( !notPrime[x] ) {
			prime[primeCnt++] = x;
			mu[x] = -1;
			f[x] = 1;
		}
		for ( int i = 0; i < primeCnt && prime[i] * x <= kNMax-1; i ++ ) {
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

	for ( int i = 2; i <= kNMax-1; i ++ )
		sumf[i] = sumf[i - 1] + f[i];
}



int main() {
	prework();
	int tst;
	scanf("%d", &tst);
	while ( tst -- ) {
		int n, m;
		scanf("%d%d", &n, &m);

		ll ans = 0;

		for ( int i = 1; i <= min(n, m);  ) {
			int j = min(n / (n / i), m / (m / i));
			ans += (ll)(n / i) * (m / i) * (sumf[j] - sumf[i - 1]);
			i = j + 1;
		}

		printf("%lld\n", ans);
	}
}
