#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int N, M, seed;
int swp[1111][2], perm[1111];
bool arr[111], ans[111];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for ( int i = 1; i <= M; i ++ ) {
		scanf("%d%d", &swp[i][0], &swp[i][1]);
		perm[i] = i;
	}
	do {
		memset(arr, 0, sizeof(arr));
		arr[1] = 1;
		for ( int i = 1; i <= M; i ++ ) {
			int x = perm[i];
			swap(arr[swp[x][0]], arr[swp[x][1]]);
		}
		for ( int i = 1; i <= N; i ++ ) 
			if ( arr[i] == 1 )
				ans[i] = true;
	} while (next_permutation(perm + 1, perm + 1 + M));
	for ( int i = 1; i <= N; i ++ )
		if ( ans[i] )
			printf("%d ", i);
}
