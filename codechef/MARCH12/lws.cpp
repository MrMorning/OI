#include <cstdio>
#include <cstring>
int f[2][26][26];
char str[2010];
void upd(int &a, int b) {
	if ( b > a )
		a = b;
}
void solve() {
	scanf("%s", str);
	int n = strlen(str);
	memset(f[0], -0x3f, sizeof(f[0]));
	f[0][0][25] = 0;
	for ( int i = 0; i < n; i ++ ) {
		memset(f[(i + 1) & 1], -0x3f, sizeof(f[i & 1]));
		for ( int j = 0; j < 26; j ++ )
			for ( int k = 0; k < 26; k ++ )
				if ( f[i & 1][j][k] >= 0 ) {
					upd(f[(i + 1) & 1][j][k], f[i & 1][j][k]);
					int t = str[i] - 'a';
					if ( t >= j )
						upd(f[(i + 1) & 1][t][k], f[i & 1][j][k] + 1);
					if ( t <= k )
						upd(f[(i + 1) & 1][j][t], f[i & 1][j][k] + 1);
				}
	}
	int ans = 0;
	for ( int j = 0; j < 26; j ++ )
		for ( int k = 0; k < 26; k ++ )
			upd(ans, f[n & 1][j][k]);
	printf("%d\n", ans);
}

int main() {
	freopen("lws.in", "r", stdin);
	freopen("lws.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
