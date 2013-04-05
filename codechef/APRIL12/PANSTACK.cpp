#include <cstdio>
typedef long long ll;
const int MOD = 1000000007;
int f[1011][1011];
int main() {
	int TST;

	f[1][1] = 1;
	for ( int i = 1; i <= 1000; i ++ )
		for ( int j = 1; j <= 1000; j ++ )
			if ( f[i][j] ) {
				f[i + 1][j] += (ll)j * f[i][j] % MOD;
				f[i + 1][j] %= MOD;
				f[i + 1][j + 1] += f[i][j];
				f[i + 1][j + 1] %= MOD;
			}

	scanf("%d", &TST);
	while ( TST -- ) {
		int N;

		scanf("%d", &N);
		int res = 0;
		for ( int j = 1; j <= 1000; j ++ ) 
			res = (res + f[N][j]) % MOD;
		printf("%d\n", res);
	}
}
