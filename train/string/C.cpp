#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N_MAX = 10000 + 5, M_MAX = 75 + 5;
const int inf = 0x3f3f3f3f;

void KMP(int *res, char *s, int n) {
	res[0] = -1;
	int t = -1;
	for ( int i = 1; i < n; i ++ ) {
		while ( t >= 0 && s[i] != s[t + 1] )
			t = res[t];
		if ( s[t + 1] == s[i] )
			t ++;
		res[i] = t;
	}
	for ( int i = 0; i < n; i ++ )
		res[i] ++;
}
bool H[N_MAX], W[M_MAX];
int N, M;
char str[N_MAX][M_MAX];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for ( int i = 0; i < N; i ++ )
		scanf("%s", str[i]);
	memset(H, -1, sizeof(H));
	memset(W, -1, sizeof(W));
	for ( int i = 0; i < N; i ++ ) {
		static int pre[M_MAX];
		static bool have[M_MAX];
		KMP(pre, str[i], M);
		memset(have, 0, sizeof(bool) * (M + 1));

		int t = M - 1;
		while ( 1 ) {
			have[M - pre[t]] = true;
			if ( t <= 0 )
				break;
			t = pre[t] - 1;
		}	

		for ( int i = 1; i <= M; i ++ )
			if ( !have[i] )
				W[i] = false;
	}
	for ( int i = 0; i < M; i ++ ) {
		static int pre[N_MAX];
		static bool have[N_MAX];
		static char ts[N_MAX];

		for ( int k = 0; k < N; k ++ )
			ts[k] = str[k][i];

		KMP(pre, ts, N);
		memset(have, 0, sizeof(bool) * (N + 1));

		int t = N - 1;
		while ( 1 ) {
			have[N - pre[t]] = true;
			if ( t <= 0 )
				break;
			t = pre[t] - 1;
		}	

		for ( int i = 1; i <= N; i ++ )
			if ( !have[i] )
				H[i] = false;
	}

	int res = inf;
	for ( int i = 1; i <= N; i ++ )
		if ( H[i] )
		for ( int j = 1; j <= M; j ++ )
			if ( W[j] )
				res = min(res, i * j);
	printf("%d\n", res);
}
