#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int D_MAX = 50;
int e[4][10];
int f[D_MAX][4];
int res[D_MAX];

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	memset(e, 0, sizeof(e));
	e[0][6] = 1;
	e[1][6] = 2;
	e[2][6] = 3;
	for ( int i = 0; i < 10; i ++ )
		e[3][i] = 3;
	f[0][0] = 1;
	for ( int i = 0; i < D_MAX; i ++ ) 
		for ( int t = 0; t < 4; t ++ )
			if ( f[i][t] )
				for ( int x = 0; x < 10; x ++ )
					f[i + 1][e[t][x]] += f[i][t];
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		int rank;
		scanf("%d", &rank);
		int n_dig;
		for ( n_dig = 1; f[n_dig][3] < rank; n_dig ++ );
		rank -= f[n_dig - 1][3];
		int six_cnt = 0;
		for ( int i = n_dig; i >= 1; i -- ) {
			int x;
			for ( x = i == n_dig; x < 10; x ++ ) {
				int tmp = f[i - 1][3];
				if ( six_cnt >= 3 ) {
					tmp += f[i - 1][0] + f[i - 1][1] + f[i - 1][2];
				} else
					if ( x == 6 ) {
						tmp += f[i - 1][2];
						if ( six_cnt >= 1 ) // two 6s
							tmp += f[i - 1][1];
						if ( six_cnt >= 2 ) // three 6s
							tmp += f[i - 1][0];
					}
				if ( rank <= tmp )
					break;
				rank -= tmp;
			}
			if ( x == 6 ) {
				six_cnt ++;
			} else if ( six_cnt < 3 )
				six_cnt = 0;
			res[i] = x;
		}
		for ( int i = n_dig; i >= 1; i -- )
			printf("%d", res[i]);
		puts("");
	}
}
