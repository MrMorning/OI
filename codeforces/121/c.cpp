#include <cstdio>

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ ) {
		scanf("%d%d", &a, &b);
		a --, b --;
		addEdge(a, b, i);
		addEdge(b, a, i);
	}
	dfs(0);
}
