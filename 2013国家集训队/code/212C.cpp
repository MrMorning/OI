#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

ll f[111][2];
char str[111];

ll work(char *s, int n) {
	memset(f, 0, sizeof(f));
	f[0][0] = f[0][1] = 1;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < 2; j ++ )
			if ( f[i][j] ) {
				if ( i+1 < n ) {
					for ( int k = 0; k < 2; k ++ ) {
						if ( j == 0 && k == 1 ) {
							if ( s[i]=='B' && s[i+1]=='A' ) {
								f[i+2][0] += f[i][j];
								f[i+2][1] += f[i][j];
							}
						} else if ( s[i]==j+'A' )
							f[i+1][k] += f[i][j];
					}
				} else {
					if ( s[i] == j+'A' )
						f[n][0] += f[i][j];
				}
			}
	return f[n][0];
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s", str+1);
	int n = strlen(str+1);
	ll ans = work(str+1, n);
	if ( str[1] == 'A' && str[n] == 'B' )
		ans += work(str+2, n-2);
	else if ( str[1] == 'B' && str[n] == 'A' ) {
		ans = 0;
		if ( str[2] == 'A' )
			ans += work(str+3, n-2);
		if ( str[n-1] == 'B' )
			ans += work(str+1, n-2);
		if ( str[2] == 'A' && str[n-1] == 'B' )
			ans -= work(str+3, n-4);
	}
	printf(LL_FMT "\n", ans);
}
