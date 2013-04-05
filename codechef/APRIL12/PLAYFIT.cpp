#include <cstdio>
#include <algorithm>
using namespace std;
int f[111111], g[111111];
void solve() {
	int N;

	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d", &g[i]);
	f[N] = g[N];
	for ( int i = N - 1; i >= 1; i -- )
		f[i] = max(f[i + 1], g[i]);
	int best = -1;
	for ( int i = 1; i < N; i ++ )
		best = max(best, f[i + 1] - g[i]);
	if ( best <= 0 )
		printf("UNFIT\n");
	else
		printf("%d\n", best);
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;

	scanf("%d", &TST);
	while ( TST -- ) 
		solve();
}
