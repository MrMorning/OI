#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const ll kInf = 0x3f3f3f3f3f3f3f3fLL;
int n, a[111111];
ll pre[111111], sodd[111111], suf[111111];

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ )
		scanf("%d", &a[i]);
	pre[0] = 0;
	for ( int i = 1; i < n ; i ++ ) {
		if ( a[i-1] == 1 ) 
			pre[i] = 0;
		else
			pre[i] = pre[i - 1] + a[i-1]/2*2;
	}
	suf[n-1] = 0;
	for ( int i = n - 2; i >= 0; i -- ) {
		if ( a[i] == 1 )
			suf[i] = 0;
		else
			suf[i] = suf[i+1] + a[i]/2*2;
	}
	sodd[0] = 0;
	for ( int i = 1; i < n; i ++ ) {
		sodd[i] = sodd[i-1] + ((a[i-1] & 1) ? a[i-1] : a[i-1] - 1);
	}
	ll ans = 0, tmp = -kInf;
	for ( int r = 0; r < n; r ++ ) {
		tmp = max(tmp, pre[r]-sodd[r]);
		ans = max(ans, tmp + suf[r] + sodd[r]);
	}
	printf(LL_FMT "\n", ans);
}
