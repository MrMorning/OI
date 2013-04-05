#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 222;
int mat[N_MAX][N_MAX], mat1[N_MAX][N_MAX], mat2[N_MAX][N_MAX];

void elim(int mat[N_MAX][N_MAX], int N, int M) {
	for ( int i = 1, j = 1; i <= M; i ++ ) {
		int p;
		for ( p = j; p <= N; p ++ )
			if ( mat[p][i] )
				break;
		if ( p == N + 1 )
			continue;
		for ( int k = 1; k <= M; k ++ )
			swap(mat[j][k], mat[p][k]);
		for ( p = 1; p <= N; p ++ )
			if ( p != j && mat[p][i] )
				for ( int k = 1; k <= M; k ++ )
					mat[p][k] ^= mat[j][k];
		j ++;
	} 
}

bool haveSol(int mat[N_MAX][N_MAX], int N, int M) {
	for ( int i = 1; i <= N; i ++ ) {
		bool allZero = true;
		for ( int j = 1; j < M; j ++ )
			allZero &= mat[i][j] == 0;
		if ( allZero && mat[i][M] )
			return false;
	}
	return true;
}

void printSol(int mat[N_MAX][N_MAX], int N, int M) {
	static int ans[N_MAX];
	memset(ans, 0, sizeof(ans));
	for ( int i = 1; i <= N; i ++ ) {
		int t;
		for ( t = 1; t < M && !mat[i][t]; t ++ );
		if ( t == M )
			continue;
		ans[t] = mat[i][M];
	}
	int cnt = 0;
	for ( int i = 1; i <= N; i ++ )
		if ( ans[i] )
			cnt ++;
	printf("%d\n", cnt);
	bool first = true;
	for ( int i = 1; i <= N; i ++ )
		if ( ans[i] ) {
			if ( first ) {
				first = false;
				printf("%d", i);
			} else
				printf(" %d", i);
		}
	printf("\n");
}

int main() {
	freopen("t.in", "r", stdin);
	int N;
	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ ) {
		int k;
		scanf("%d", &k);
		while ( k -- ) {
			int x;
			scanf("%d", &x);
			mat[x][i] = 1;
		}
	}
	memcpy(mat1, mat, sizeof(mat));
	memcpy(mat2, mat, sizeof(mat));
	for ( int i = 1; i <= N; i ++ ) {
		int t;
		scanf("%d", &t);
		mat1[i][N + 1] = t;
		mat2[i][N + 1] = !t;
	}
	elim(mat1, N, N + 1);
	elim(mat2, N, N + 1);
	if ( haveSol(mat1, N, N + 1) ) 
		printSol(mat1, N, N + 1);
	else if ( haveSol(mat2, N, N + 1) )
		printSol(mat2, N, N + 1);
	else
		printf("-1\n");
}
