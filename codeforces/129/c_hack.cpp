#include <cstdio>
int n = 200000;
int main() {
	freopen("t.in", "w", stdout);
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ )
		printf("A");
	puts("");
	for ( int i = 0; i < n; i ++ )
		printf("A");
	puts("");
}
