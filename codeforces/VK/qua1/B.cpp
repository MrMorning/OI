#include <cstdio>
int f[5], n;
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		int t;
		scanf("%d", &t);
		f[t] ++;
	}
	int ans = f[4];
	f[4] = 0;
	if ( f[1] <= f[3] ) {
		ans += f[3];
		f[1] = f[3] = 0;
	} else {
		ans += f[3] + (f[1] - f[3]) / 4;
		f[1] = (f[1] - f[3]) % 4;
		f[3] = 0;
	}
	ans += f[2] / 2;
	f[2] %= 2;
	if ( f[1] + 2 * f[2] != 0 ) {
		if ( f[1] + 2 * f[2] <= 4 )
			ans += 1;
		else
			ans += 2;
	}
	printf("%d\n", ans);
}
