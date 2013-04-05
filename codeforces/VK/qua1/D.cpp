#include <cstdio>
int n, a[20000], sum[20000];
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &a[i]);
	int ans = -0x3f3f3f3f;
	for ( int x = 1; x <= n; x ++ )
		if ( n % x == 0 && n / x >= 3 ) {
			for ( int i = 0; i < x; i ++ )
				sum[i] = 0;
			for ( int i = 0; i < n; i ++ )
				sum[i % x] += a[i];
			for ( int i = 0; i < x; i ++ )
				if ( sum[i] > ans )
					ans = sum[i];
		}
	printf("%d\n", ans);
}
