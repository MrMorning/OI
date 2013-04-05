#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int TRY_TIMES = 10000;

int E1[77][77], E2[77][77];
int perm[77], out[77];
int N;

int eval() {
	int res = 0;
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			if ( E1[i][j] && E2[perm[i]][perm[j]] )
				res ++;
	return res;
}

void solve() {

	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			scanf("%d", &E1[i][j]);
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			scanf("%d", &E2[i][j]);

	for ( int i = 1; i <= N; i ++ )
		perm[i] = i;
	int ans = -1;

	for ( int rep = 0; rep < TRY_TIMES; rep ++ ) {
		int tmp = eval();
		if ( tmp > ans ) {
			ans = tmp;
			memcpy(out, perm, sizeof(perm));
		}
		random_shuffle(perm + 1, perm + 1 + N);
	}

	for ( int i = 1; i <= N; i ++ )
		printf("%d ", i);
	printf("\n");
	static int res[77];
	for ( int i = 1; i <= N; i ++ )
		res[out[i]] = i;
	for ( int i = 1; i <= N; i ++ )
		printf("%d ", res[i]);
	printf("\n");
}

int main() {
	srand(55);
//	freopen("t.in", "r", stdin);
	int TST;

	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
