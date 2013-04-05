#include <cstdio>
#include <map>
#include <cstdlib>
using namespace std;
int n, m, B[101], A[22];
map<int, int> cnt;

void dfs(int cur) {
	if ( cur > n ) {
		for ( int i = 1; i <= n; i ++ )
			printf("%d ", A[i]);
		exit(0);
	}
	for ( int i = 1; i <= m; i ++ )
		if ( cnt[B[i]] > 0) {
			bool fail = false;
			for ( int j = 1; j < cur; j ++ )
				if ( cnt[B[i]^A[j]] == 0 ) {
					fail = true;
					break;
				}
			if ( !fail ) {
				A[cur] = B[i];
				for ( int j = 1; j < cur; j ++ )
					cnt[B[i]^A[j]]--;
				dfs(cur+1);
				A[cur] = 0;
				for ( int j = 1; j < cur; j ++ )
					cnt[B[i]^A[j]]++;
			}
		}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &m);
	for ( int i = 1; i <= m; i ++ ) {
		scanf("%d", &B[i]);
		cnt[B[i]]++;
	}
	for ( n = 1; n*(n-1)/2 != m; n ++ );
	A[1] = 0;
	dfs(2);
}
