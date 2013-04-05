#include <cstdio>
#include <algorithm>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
using namespace std;
int n;
ll a[111];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf(LL_FMT, &a[i]);
	for ( int d = 59, j = 1; d >= 0; d -- ) {
		int p;
		for ( p = j; p <= n; p ++ )
			if ( a[p] & (1LL << d) ) 
				break;
		if ( p == n + 1 )
			continue;
		swap(a[j], a[p]);
		for ( p = 1; p <= n; p ++ )
			if ( p != j )
				if ( a[p] & (1LL << d) )
					a[p] ^= a[j];
		j ++;
	}
	ll ans = 0;
	for ( int i = 1; i <= n; i ++ )
		ans ^= a[i];
	printf(LL_FMT "\n", ans);
}
