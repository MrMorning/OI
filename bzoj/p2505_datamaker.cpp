#include <cstdio>
#include <cstdlib>
int seed;
typedef long long ll;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	ll l = (ll)rand() * rand() + 1, r = (ll)rand() * rand(),
		k = rand() % 1000 + 1;
	if ( l > r )
		printf("%lld %lld %lld\n", r, l, k);
	else
		printf("%lld %lld %lld\n", l, r, k);
}
