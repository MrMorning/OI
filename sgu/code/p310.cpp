#include <cstdio>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
int n, m, k;
ll f[61][1<<15];
int cnt[1<<15];
int countBits(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	int upperlim = 1 << m;
	for ( int s = 0; s < upperlim; s ++ ) {
		cnt[s] = countBits(s);
		if ( cnt[s] >= k ) 
			f[m][s] = 1;
	}
	for ( int i = m; i < n; i ++ ) 
		for ( int s = 0; s < upperlim; s ++ ) 
			if ( f[i][s] ) {
				int ns;
				ns = (s << 1) & (upperlim - 1);
				if ( cnt[ns] >= k )
					f[i + 1][ns] += f[i][s];
				ns += 1;
				if ( cnt[ns] >= k )
					f[i + 1][ns] += f[i][s];
			}
	ll ans = 0;
	for ( int s = 0; s < upperlim; s ++ )
		if ( cnt[s] >= k )
			ans += f[n][s];
	printf(LL_FMT "\n", ans);
}
