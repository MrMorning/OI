#include <cstdio>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
bool dpDone[101][11][11][11][11];
int dpMemo[101][11][11][11][11];
int A[11], B[11], M, N;
int dp(int n, int p0, int p1, int p2, int p3) {
	if ( n >= M )
		return 0;
	if ( dpDone[n][p0][p1][p2][p3] )
		return dpMemo[n][p0][p1][p2][p3];
	dpDone[n][p0][p1][p2][p3] = true;
	int &val = dpMemo[n][p0][p1][p2][p3] = inf;
	if ( p0 != 0 )
		val = min(val, dp(n, 0, p0, p1, p2) + 1);
	for ( int i = 1; i <= N; i ++ ) {
		if ( B[i] == 1 && p0 == i ) continue;
		if ( B[i] == 2 && (p0 == i || p1 == i) ) continue;
		if ( B[i] == 3 && (p0 == i || p1 == i || p2 == i) ) continue;
		if ( B[i] == 4 && (p0 == i || p1 == i || p2 == i || p3 == i) ) continue;
		val = min(val, dp(n + A[i], i, p0, p1, p2) + 1);
	}
	if ( p0 != 0 || p1 != 0 || p2 != 0 || p3 != 0 )
		val = min(val, dp(n, 0, p0, p1, p2) + 1);
	return val;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &M, &N);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d%d", &A[i], &B[i]);
	printf("%d\n", dp(0, 0, 0, 0, 0));
}
