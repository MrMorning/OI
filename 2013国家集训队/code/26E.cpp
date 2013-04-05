#include <cstdio>
#include <cassert>
#include <cstdlib>

int tmp[200010], rear[200010];
bool mark[200010];
int n[105];
int N, W;

void noSol() {
	puts("No");
	exit(0);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &W);
	int sum = 0;
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%d", &n[i]);
		sum += n[i];
	}
	if ( !(1 <= W && W <= sum) ) 
		noSol();
	if ( N == 1 && W == n[1] ) {
		printf("Yes\n");
		for ( int i = 0; i < 2*n[1]; i ++ )
			printf("1 ");
	} else if ( N >= 2 && W >= 2 ) {
		printf("Yes\n");
		int nTmp = 0;
		tmp[nTmp++] = 1;
		for ( int i = 3; i <= N; i ++ )
			for ( int k = 0; k < n[i]; k ++ ) {
				tmp[nTmp++] = i;
				tmp[nTmp++] = i;
				mark[nTmp-2] = mark[nTmp-1] = true;
			}
		for ( int i = 0; i < n[2]-1; i ++ ) {
			tmp[nTmp++] = 2;
			tmp[nTmp++] = 2;
			mark[nTmp-1] = mark[nTmp-2] = true;
		}
		tmp[nTmp++] = 1;
		tmp[nTmp++] = 2;
		for ( int i = 0; i < n[1]-1; i ++ ) {
			tmp[nTmp++] = 1;
			tmp[nTmp++] = 1;
			mark[nTmp-1] = mark[nTmp-2] = true;
		}
		tmp[nTmp++] = 2;

		int left = W-2;
		int nRear = 0;
		for ( int i = 0; i < nTmp; i ++ )
			if ( !mark[i] || left == 0 )
				printf("%d ", tmp[i]);
			else {
				assert(mark[i+1]);
				rear[nRear++] = tmp[i];
				rear[nRear++] = tmp[i];
				left--;
				i++;
			}
		for ( int i = 0; i < nRear; i ++ )
			printf("%d ", rear[i]);
	} else if ( N >= 2 && W == 1 ) {
		bool hasOne = false;
		for ( int i = 1; i <= N; i ++ ) 
			if ( n[i] == 1 ) {
				printf("Yes\n");
				printf("%d ", i);
				for ( int j = 1; j <= N; j ++ )
					if ( i != j )
						for ( int k = 0; k < n[j]; k ++ )
							printf("%d %d ", j, j);
				printf("%d ", i);
				hasOne = true;
				break;
			}
		if ( !hasOne ) noSol();
	} else noSol();
}
