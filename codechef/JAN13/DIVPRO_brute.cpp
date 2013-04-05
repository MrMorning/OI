#include <cstdio>
typedef long long ll;

int ans = 0;

void dfs(int i, ll up, ll down, int L, ll V) {
	if ( i == L ) {
		ans += (up % down == 0 && up / down == V);
		return;
	}
	for ( int x = 0; x <= 9; x ++ ) {
		if ( x == 0 && (i == 0 || i & 1) ) continue;
		if ( i & 1 ) {
			dfs(i + 1, up, down * x, L, V);
		} else dfs(i + 1, up * x, down, L, V);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		int L;
		ll V;
		scanf("%d%lld", &L, &V);
		ans = 0;
		dfs(0, 1LL, 1LL, L, V);
		printf("%d\n", ans);
	}
}
