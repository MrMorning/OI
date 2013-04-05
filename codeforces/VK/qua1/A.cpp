#include <cstdio>
int n, k, a[55];
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &k);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &a[i]);
	int des = a[k - 1];
	int ans = 0;
	for ( int i = 0; i < n; i ++ )
		if ( a[i] > 0 && a[i] >= des )
			ans ++;
	printf("%d\n", ans);
}
