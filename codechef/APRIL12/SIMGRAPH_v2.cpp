#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double INIT_TEMP = 1000;
const double FINAL_TEMP = 1e-3;
const double FREEZE = 0.98;
const int TRY_TIMES = 30;

int E1[77][77], E2[77][77];
int perm[77], out[77];
int N;

int eval() {
	int res = 0;
	for ( int i = 1; i <= N; i ++ )
		for ( int j = i + 1; j <= N; j ++ )
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
	int cur_energy = eval();
	int ans = -1;

	for ( double cur_temp = INIT_TEMP; cur_temp > FINAL_TEMP; cur_temp *= FREEZE ) 
		for ( int rep = 0; rep < TRY_TIMES; rep ++ ) {
			int u = rand() % N + 1, v = rand() % N + 1;

			if ( cur_energy > ans ) {
				ans = cur_energy;
				memcpy(out, perm, sizeof(perm));
			}

			swap(perm[u], perm[v]);
			int nxt_energy = eval();
			if ( nxt_energy > cur_energy || (exp((nxt_energy - cur_energy) / cur_temp)) > (double)rand() / RAND_MAX )
				cur_energy = nxt_energy;
			else
				swap(perm[u], perm[v]);
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
	freopen("t.in", "r", stdin);
	int TST;

	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
