#include <cstdio>
typedef long long ll;
int n, k1, k2, p1, p2, p3;
int ceildiv(int a, int b) {
	if ( a % b == 0 )
		return a / b;
	return a / b + 1;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d%d%d", &n, &k1, &k2, &p1, &p2, &p3);
	if ( n < p1 ) {
		puts("0");
		return 0;
	}
	int ans = k1;
	n -= p1;
	if ( n < (ll)k2 * p2 ) {
		ans += ceildiv(n, p2);
		printf("%d\n", ans);
		return 0;
	}
	ans += k2;
	n -= k2 * p2;
	
	ans += ceildiv(n, p3);
	printf("%d\n", ans);
}
