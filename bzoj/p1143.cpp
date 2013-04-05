#include <cstdio>
#include <cstring>
int N, M;
int match[111];
bool vis[111];
bool ed[111][111], ed2[111][111];

bool dfs(int x) {
	for ( int y = 0; y < N; y ++ ) 
		if ( ed2[x][y] ) {
			if ( vis[y] ) continue;
			vis[y] = true;
			if ( match[y] == -1 || dfs(match[y]) ) {
				match[y] = x;
				return true;
			}
		}
	return false;
}

void dfs2(int x) {
	vis[x] = true;
	for ( int y = 0; y < N; y ++ )
		if ( ed[x][y] && !vis[y] )
			dfs2(y);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	while ( M -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a --,  b --;
		ed[a][b] = true;
	}
	for ( int i = 0; i < N; i ++ ) {
		memset(vis, 0, sizeof(bool) * N);
		dfs2(i);
		for ( int j = 0; j < N; j ++ )
			if ( j != i && vis[j] ) 
				ed2[i][j] = true;
	}
	memset(match, -1, sizeof(int) * N);
	int ans = 0;
	for ( int i = 0; i < N; i ++ ) {
		memset(vis, 0, sizeof(bool) * N);
		ans += dfs(i);
	}
	printf("%d\n", N - ans);
}
