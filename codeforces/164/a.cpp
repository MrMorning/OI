#include <cstdio>
int h[55], a[55], n;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d%d", &h[i], &a[i]);
	int ans = 0;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < n; j ++ )
			if ( i != j && a[j] == h[i] )
				ans++;
	printf("%d\n", ans);
}
