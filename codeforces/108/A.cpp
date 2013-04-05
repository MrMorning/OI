#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, grade[111][111], best[111];
bool suc[111];
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char str[111];
		scanf("%s", str + 1);
		for ( int j = 1; j <= m; j ++ ) 
			grade[i][j] = str[j] - '0';
	}
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			best[j] = max(best[j], grade[i][j]);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( grade[i][j] == best[j] )
				suc[i] = true;
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		if ( suc[i] )
			res ++;
	printf("%d\n", res);
}
