#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, k, p;
int mat[1010][1010];

int powMod(int a, int n) {
	int res = n & 1 ? a % p: 1 % p;
	for ( n >>= 1; n; n >>= 1 ) {
		a = (long long)a * a % p;
		if ( n & 1 ) 
			res = (long long)res * a % p;
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	if ( (n + m) & 1 ) {
		puts("0");
		return 0;
	}	
	scanf("%d", &k);
	for ( int i = 0; i < k; i ++ ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if ( k >= n ) mat[b][a] = c;
		else mat[a][b] = c;	
	}
	if ( k >= n ) 
		swap(n, m);
	for ( int i = 1; i <= n; i ++ ) {
		bool b = true;
		for ( int j = 1; j <= m; j ++ )
			b &= mat[i][j] == 0;
		if ( b ) {
			for ( int k = 1; k <= m; k ++ )
				swap(mat[n][k], mat[i][k]);
			break;
		}
	}
	int unfixedCnt = 0;
	for ( int i = 1; i < n; i ++ ) {
		int cnt = 0;
		for ( int j = 1; j <= m; j ++ )
			cnt += mat[i][j] == 0;
		if ( cnt == 0 ) {
			int tmp = 1;
			for ( int j = 1; j <= m; j ++ )
				tmp *= mat[i][j];
			if ( tmp != -1 ) {
				puts("0");
				return 0;
			}
		} else unfixedCnt += cnt-1;
	}
	scanf("%d", &p);
	printf("%d\n", powMod(2, unfixedCnt));
}
