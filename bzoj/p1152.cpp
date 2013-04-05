#include <cstdio>
const int MOD = 10000;
int str[100010], pre[100010];
int powMod(int a, int n) {
	a %= MOD;
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = a * a % MOD;
		if ( n & 1 )
			res = res * a % MOD;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	int N, T;
	scanf("%d%d", &N, &T);
	while ( T -- ) {
		int len;
		scanf("%d", &len);
		for ( int i = 1; i <= len; i ++ )
			scanf("%d", &str[i]);
		pre[0] = -1;
		pre[1] = 0;
		for ( int i = 2; i <= len; i ++ ) {
			int t = pre[i - 1];
			while ( t >= 0 && str[t + 1] != str[i] )
				t = pre[t];
			if ( t >= 0 && str[t + 1] == str[i] )
				pre[i] = t + 1;
			else
				pre[i] = 0;
		}
		int res = 0;
		for ( int i = len; i >= 1; i = pre[i] ) 
			res = (res + powMod(N, i)) % MOD;
		printf("%04d\n", res);
	}
}
