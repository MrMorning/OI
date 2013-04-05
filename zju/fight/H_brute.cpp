#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N_MAX = 1010;
int arr[N_MAX][N_MAX];
int N, M, C;

int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d%d", &N, &M, &C) != EOF ) {
		for ( int i = 1; i <= N; i ++ )
			for ( int j = 1; j <= M; j ++ )
				arr[i][j] = 0;
		while ( C -- ) {
			int a, b, h, x, y;
			scanf("%d%d%d%d%d", &a, &b, &h, &x, &y);
			x ++, y ++;
			int tmp = 0;
			for ( int i = x; i < x + a; i ++ )
				for ( int j = y; j < y + b; j ++ )
					tmp = max(tmp, arr[i][j]);
			for ( int i = x; i < x + a; i ++ )
				for ( int j = y; j < y + b; j ++ )
					arr[i][j] = tmp + h;
		}
		int res = 0;
		for ( int i = 1; i <= N; i ++ )
			for ( int j = 1; j <= M; j ++ )
				res = max(res, arr[i][j]);
		printf("%d\n", res);
	}

}	

