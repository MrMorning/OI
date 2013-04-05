#include <cstdio>
int N, M, K, cnt;
int C[55], arr[55];
bool found;

int count_lucky(int x) {
	int res = 0;
	while ( x ) {
		res += x % 10 == 4 || x % 10 == 7;
		x /= 10;
	}
	return res;
}

bool check() {
	for ( int i = 1; i < N; i ++ ) {
		int a = count_lucky(arr[i]), b = count_lucky(arr[i + 1]);
		if ( C[i] && a != b )
			return false;
		if ( !C[i] && a == b )
			return false;
	}
	return true;
}

void dfs(int i) {
	if ( i == N + 1 ) {
		if ( check() ) {
			cnt ++;
			if ( cnt == K ) {
				found = true;
				return;
			}
		}
		return;
	}

	for ( int x = 1; x <= M; x ++ ) {
		arr[i] = x;
		dfs(i + 1);
		if ( found )
			return;
		arr[i] = 0;
	}
}

void solve() {
	scanf("%d%d%d", &N, &M, &K);
	for ( int i = 1; i < N; i ++ )
		scanf("%d", &C[i]);
	cnt = 0;
	found = false;
	dfs(1);
	if ( !found )
		puts("-1");
	else {
		for ( int i = 1; i <= N; i ++ )
			printf("%d ", arr[i]);
		puts("");
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;

	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
