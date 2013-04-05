#include <cstdio>
#include <cstring>

const int N_MAX = 1005;
const int MOD = 1000000007;

int f[N_MAX][N_MAX][2];

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
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j <= n; j ++ ) {
			if ( f[i][j][0] ) {
				for ( int x = 0; x <= 9; x ++ ) 
					upd(f[i + 1][j + test(x)][0], f[i][j][0]);
			}
			if ( f[i][j][1] ) {
				for ( int x = 0; x < num[i] - '0'; x ++ )
					upd(f[i + 1][j + test(x)][0], f[i][j][1]);
				upd(f[i + 1][j + test(num[i] - '0')][1], f[i][j][1]);
			}
		}
	int res = 0;
	for ( int x = 0; x <= n; x ++ )
		if ( is_lucky(x) ) {
			upd(res, f[n][x][0]);
			if ( inclusive )
				upd(res, f[n][x][1]);
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
