#include <cstdio>
#include <algorithm>
using namespace std;
const int kInf = 0x3f3f3f3f;
int n, w[300][300];
int f[601][300][300];
void upd(int &a, int b) {
	a = max(a, b);
}
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < n; j ++ )
			scanf("%d", &w[i][j]);
	for ( int i = 0; i <= 2*n-2; i ++ ) 
		for ( int x1 = 0; x1 < n; x1 ++ )
			for ( int x2 = 0; x2 < n; x2 ++ )
				f[i][x1][x2] = -kInf;
	f[0][0][0] = w[0][0];
	for ( int i = 0; i < 2*n-2; i ++ ) 
		for ( int x1 = 0; x1 <= min(i, n-1); x1 ++ )
			for ( int x2 = 0; x2 <= min(i, n-1); x2 ++ ) {
				int y1 = i-x1, y2 = i-x2;
				if ( x1 < n-1 && x2 < n-1 )
					upd(f[i+1][x1+1][x2+1], f[i][x1][x2]+(x1==x2?w[x1+1][y1]:w[x1+1][y1]+w[x2+1][y2]));
				if ( x1 < n-1 && y2 < n-1 )
					upd(f[i+1][x1+1][x2], f[i][x1][x2]+(x1+1==x2?w[x1+1][y1]:w[x1+1][y1]+w[x2][y2+1]));
				if ( y1 < n-1 && x2 < n-1 )
					upd(f[i+1][x1][x2+1], f[i][x1][x2]+(x1==x2+1?w[x1][y1+1]:w[x1][y1+1]+w[x2+1][y2]));
				if ( y1 < n-1 && y2 < n-1 )
					upd(f[i+1][x1][x2], f[i][x1][x2]+(x1==x2?w[x1][y1+1]:w[x1][y1+1]+w[x2][y2+1]));
			}
	printf("%d\n", f[2*n-2][n-1][n-1]);
}
