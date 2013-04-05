#include <cstdio>
int fa[111];
int f[111][111];
bool okay[111];
int n, m;

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	fa[find(x)] = find(y);
}

bool isSame(int i, int j) {
	for ( int k = 0; k < m; k ++ )
		if ( f[i][k] != f[j][k] )
			return false;
	return true;
}

bool noRequire(int i) {
	for ( int k = 0; k < m; k ++ )
		if ( f[i][k] )
			return false;
	return true;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < m; i ++ ) {
		int t;
		scanf("%d", &t);
		while ( t -- ) {
			int x;
			scanf("%d", &x);
			x --;
			f[x][i] = true;
		}
	}
	for ( int i = 0; i < n; i ++ )
		fa[i] = i;
	int ans = n;
	for ( int i = 0; i < n; i ++ ) {
		okay[i] = !noRequire(i);
		if ( !okay[i] )
			ans --;
	}
	for ( int i = 0; i < n; i ++ )
		if ( okay[i] )
			for ( int j = i + 1; j < n; j ++ )
				if ( okay[j] )
					if ( isSame(i, j) && find(i) != find(j) )
						merge(i, j), ans --;
	printf("%d\n", ans);
}
