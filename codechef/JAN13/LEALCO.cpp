#include <cstdio>
#include <algorithm>
using namespace std;
int N, K, M, R[111], A[111];
int countBits(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d%d%d", &N, &K, &M);
		for ( int i = 0; i < N; i ++ )
			scanf("%d", &R[i]);
		int upperlim = 1 << N;
		int ans = 0x3f3f3f3f;
		for ( int s = 0; s < upperlim; s ++ ) {
			for ( int k = 0; k < N; k ++ )
				A[k] = R[k] + ((s & (1 << k)) > 0);
			bool fail = false;
			for ( int i = 0; i + K - 1 < N; i ++ ) {
				int mx = 0, cnt = 0;
				for ( int j = i; j < i + K; j ++ )
					mx = max(mx, A[j]);
				for ( int j = i; j < i + K; j ++ )
					cnt += A[j] == mx;
				if ( cnt >= M )
					fail = true;
			}
			if ( !fail )
				ans = min(ans, countBits(s));
		}
		if ( ans == 0x3f3f3f3f )
			printf("-1\n");
		else printf("%d\n", ans);
	}
}
