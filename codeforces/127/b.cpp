#include <cstdio>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const ll kInf = 0x3f3f3f3f3f3f3f3fLL;
int n, m, ansP, ansQ;
ll coef1, coef2, coef3, coef4;
int c[1010][1010];

ll sqr(ll x) { return x * x; }


int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ ) {
			scanf("%d", &c[i][j]);
			coef1 += 16 * c[i][j];
			coef2 += -8LL * c[i][j] * (4 * i + 2);
			coef3 += -8LL * c[i][j] * (4 * j + 2);
			coef4 += sqr(4LL * i + 2) * c[i][j];
			coef4 += sqr(4LL * j + 2) * c[i][j];
		}
	ll ans = kInf;
	for ( int p = 0; p <= n; p ++ )
		for ( int q = 0; q <= m; q ++ ) {
			ll tmp = 0;
			tmp += coef1 * (p * p + q * q);
			tmp += p * coef2;
			tmp += q * coef3;
			tmp += coef4;
			if ( ans > tmp ) {
				ans = tmp;
				ansP = p, ansQ = q;
			}
		}
	printf(LL_FMT "\n", ans);
	printf("%d %d\n", ansP, ansQ);
}
