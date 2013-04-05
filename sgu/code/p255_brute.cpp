#include <cstdio>
int k;
int countBits(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &k);
	int ans = 0;
	for ( int x = k + 1; x <= k + k; x ++ )
		if ( countBits(x) == 3 )
			ans ++;
	printf("%d\n", ans);
}
