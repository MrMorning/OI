#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 55, X_MAX = 222;
int f[N_MAX][X_MAX];
int a[N_MAX], b[N_MAX];
int N, X, Y;
bool check(int D) {
	memset(f, -0x3f, sizeof(f));
	f[0][0] = 0;
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 0; j <= X; j ++ ) 
			for ( int t = 0, lim = min(j, D / a[i]); t <= lim; t ++ )
				f[i][j] = max(f[i][j], f[i - 1][j - t] + (D - t * a[i]) / b[i]);
	return f[N][X] >= Y;
}
void solve() {
	scanf("%d%d%d", &N, &X, &Y);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d%d", &a[i], &b[i]);
	int lb = 0, rb = a[1] * X + b[1] * Y;
	for ( int mid = (lb + rb) / 2; lb < rb - 1; 
			mid = (lb + rb) / 2 ) 
		if ( check(mid) )
			rb = mid;
		else
			lb = mid;
	printf("%d\n", rb);
}
int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for ( int i = 1; i <= TST; i ++ ) {
		printf("Case %d: ", i);
		solve();
	}
}
