#include <cstdio>

int calc_mat(int n, int m) {
}

void solve() {
	int n, k, m;
	scanf("%d%d%d", &n, &k, &m);
	ll res = bino(n, k, m);
	res = res * calc_mat(n - k, m) % m;
	printf("%d\n", (int)res);
}

int main() {
	freopen("t.in", "r", stdin);
	int TST:
	scanf("%d", &TST);
	for ( int i = 1; i <= TST; i ++ ) {
		printf("Case %d: ", i);
		solve();
	}
}
