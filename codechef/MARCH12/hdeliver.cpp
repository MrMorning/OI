#include <cstdio>
int par[100];
int find(int x) {
	return par[x] == x ? x : par[x] = find(par[x]);
}
void merge(int a, int b) {
	int x = find(a),
		y = find(b);
	if ( x == y )
		return;
	par[x] = y;
}
void solve() {
	int N, M, Q;
	scanf("%d%d", &N, &M);
	for ( int i = 0; i < N; i ++ )
		par[i] = i;
	while ( M -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		merge(a, b);
	}
	scanf("%d", &Q);
	while ( Q -- ) {
		int u, v;
		scanf("%d%d", &u, &v);
		if ( find(u) == find(v) )
			printf("YO\n");
		else
			printf("NO\n");
	}
}

int main() {
	freopen("hdeliver.in", "r", stdin);
	freopen("hdeliver.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
