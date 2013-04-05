#include <cstdio>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
int n;
ll f[21][10][2];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int x = 0; x <= 9; x ++ )
		f[1][x][0] = 1;
	for ( int i = 1; i < n; i ++ )
		for ( int x = 0; x <= 9; x ++ ) {
			for ( int y = x; y <= 9; y ++ )
				f[i+1][y][0] += f[i][x][0];
			for ( int y = 0; y < x; y ++ )
				f[i+1][y][1] += f[i][x][0];
			for ( int y = 0; y <= x; y ++ )
				f[i+1][y][1] += f[i][x][1];
		}
	ll ans = 0;
	for ( int x = 0; x <= 9; x ++ )
		ans += f[n][x][0] + f[n][x][1];
	printf(LL_FMT "\n", ans);
}
