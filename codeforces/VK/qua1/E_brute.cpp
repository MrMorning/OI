#include <cstdio>
#include <algorithm>
using namespace std;
int st[22], la[22];
int N, K;
int count_bits(int x) {
	int res = 0;
	while ( x ) {
		res += (x & 1) > 0;
		x >>= 1;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 0; i < N; i ++ )
		scanf("%d%d", &st[i], &la[i]);
	int ans = 0;
	for ( int s = 0, lim = (1 << N); s < lim; s ++ ) 
		if ( N - count_bits(s) <= K ) {
			int pre = 0;
			for ( int i = 0; i < N; i ++ )
				if ( s & (1 << i) ) {
					if ( st[i] <= pre )
						pre += la[i];
					else {
						ans = max(ans, st[i] - pre - 1);
						pre = st[i] + la[i] - 1;
					}
				}
			ans = max(ans, 86400 - pre);
		}
	printf("%d\n", ans);
}
