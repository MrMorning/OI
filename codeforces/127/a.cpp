#include <cstdio>
typedef long long ll;
int ans[5555];
int sqr(int x) {
	return x * x;
}
int main() {
	freopen("t.in", "r", stdin);
	for ( int i = 1; i <= 5000; i ++ ) {
		int n = i;
		if ( n & 1 )
			ans[n] = (n * n + 1) / 2;
		else
			ans[n] = 4 * ((sqr((n - 2) / 2) + 1) / 2);
	}
	int x;
	scanf("%d", &x);
	if ( x == 2 ) {
		puts("3");
		return 0;
	}
	for ( int i = 1; i <= 5000; i ++ ) 
		if ( i % 2 == 0 && ans[i] >= x && (ans[i] - x) % 4 == 0 ) {
			printf("%d\n", i);
			return 0;
		} else if ( i & 1 ) { 
			if ( ans[i] - 1 >= x && (((ans[i] - 1 - x) % 4 == 0) || (i > 3 && (ans[i] - 1 - x) % 2 == 0)) ) {
				printf("%d\n", i);
				return 0;
			}
			if ( ans[i] >= x && (((ans[i] - x) % 4 == 0) || (i > 3 && (ans[i] - x) % 2 == 0)) ) {
				printf("%d\n", i);
				return 0;
			}
		}
}
