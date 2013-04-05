#include <cstdio>
#include <cstring>

typedef long long ll;
const int N_MAX = 1010;
const int MOD = 1000000007;

int f[2][N_MAX][2];

void upd(int &x, int y) {
	x += y;
	x %= MOD;
}

bool test(int x) { return x == 4 || x == 7; }
bool is_lucky(int x) {
	if ( x == 0 ) return false;
	while ( x ) {
		if ( !test(x % 10) )
			return false;
		x /= 10;
	}
	return true;
}

int calc(char num[N_MAX], bool inclusive) {
	int n = strlen(num);
	memset(f, 0, sizeof(f));
	f[0][0][1] = 1;
	for ( int i = 0; i < n; i ++ ) {
		memset(f[(i + 1) & 1], 0, sizeof(f[0]));
		for ( int j = 0; j <= n; j ++ ) {
			if ( f[i & 1][j][0] ) {
				upd(f[(i + 1) & 1][j][0], (ll)f[i & 1][j][0] * 8 % MOD);
				upd(f[(i + 1) & 1][j + 1][0], (ll)f[i & 1][j][0] * 2 % MOD);
			}
			if ( f[i & 1][j][1] ) {
				for ( int x = 0; x < num[i] - '0'; x ++ )
					upd(f[(i + 1) & 1][j + test(x)][0], f[i & 1][j][1]);
				upd(f[(i + 1) & 1][j + test(num[i] - '0')][1], f[i & 1][j][1]);
			}
		}
	}
	int res = 0;
	for ( int x = 0; x <= n; x ++ )
		if ( is_lucky(x) ) {
			upd(res, f[n & 1][x][0]);
			if ( inclusive )
				upd(res, f[n & 1][x][1]);
		}
	return res;
}
char L[N_MAX], R[N_MAX];
void solve() {
	scanf("%s%s", L, R);
	int res = calc(R, 1) - calc(L, 0);
	if ( res < 0 )
		res += MOD;
	printf("%d\n", res);
}

int main() {
	freopen("lucky2.in", "r", stdin);
	freopen("lucky2.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
