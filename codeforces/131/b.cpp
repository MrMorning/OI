#include <cstdio>
#include <cstring>
typedef long long ll;
const int MOD = 1000000007;
int bino[101][101];
int f[11][101];
int a[10], n;
void addto(int &a, int b) {
	a += b;
	a %= MOD;
	if ( a <0 ) a += MOD;
}
int mul(int a, int b) {
	return (int)((ll)a * b % MOD);
}
int solve(int n) {
	memset(f, 0, sizeof(f));
	for ( int l = a[0]; l <= n; l ++ )
		f[1][n-l] = bino[n-1][l];
	for ( int i = 1; i <= 9; i ++ ) 
		for ( int j = 0; j <= n; j ++ )
			if ( f[i][j] ){
				for ( int k = a[i]; k <= j; k ++ )
					addto(f[i+1][j-k], mul(f[i][j], bino[j][k]));
			}
	return f[10][0];
}
int main() {
	bino[0][0] = 1;
	for ( int i = 1; i <= 100; i ++ ) {
		bino[i][0] = 1;
		for ( int j = 1; j <= i; j ++ ) {
			addto(bino[i][j], bino[i-1][j-1]);
			addto(bino[i][j], bino[i-1][j]);
		}
	}
	scanf("%d", &n);
	for ( int i = 0; i <= 9; i ++ )
		scanf("%d", &a[i]);
	int ans = 0;
	for ( int k = 1; k <= n; k ++ )
		addto(ans, solve(k));
	printf("%d\n", ans);
}
