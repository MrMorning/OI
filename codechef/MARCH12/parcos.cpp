#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
typedef long double val_t;

val_t memo[35][35];
bool done[35][35];
int M, N;
val_t X;

val_t bino(int n, int k) {
	val_t res = 1.0;
	for ( int i = n - k + 1; i <= n; i ++ )
		res *= i;
	for ( int i = 1; i <= k; i ++ )
		res /= i;
	return res;
}

val_t dp(int m, int n) {
	if ( m == 0 )
		return 0.0;
	if ( m > n )
		return 0.0;
	if ( done[m][n] )
		return memo[m][n];
	done[m][n] = true;
	val_t &res = memo[m][n] = 0;
	if ( n == 1 )
		res = cos(X);
	else if ( n == 2 ) {
		if ( m == 1 )
			res = cos(2 * X);
		else
			res = cos(X) * cos(X);
	} else {
		res += cos(X) * dp(m - 1, n - 1);
		res += 2 * cos(X) * dp(m, n - 1);
		res -= dp(m, n - 2) + dp(m - 1, n - 2);
	}
	return res;
}

void solve() {
	memset(done, 0, sizeof(done));

	scanf("%d%d", &M, &N);
	cin >> X;
	X /= N;
	val_t res = 0;
	for ( int i = 1; i <= N; i ++ ) 
		res += bino(M, i) * dp(i, N);
	cout << setprecision(16) << res << '\n';
}

int main() {
	freopen("parcos.in", "r", stdin);
//	freopen("parcos.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
