#include <cstdio>
int n;
int a[222222], b[222222];
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &a[i]);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%d", &b[i]);
	for ( int i = 0, j = 0; i < n; i ++ ) {
		while ( j < n && a[i] != b[j] )
			j ++;
		if ( j == n ) {
			printf("%d\n", n - i);
			return 0;
		}
	}
	printf("0\n");
}
