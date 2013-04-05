#include <cstdio>
#include <algorithm>
using namespace std;
int n, t;
bool e[55][55];
int out[55 * 55];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &t);
	for ( int i = 1; i <= n; i ++ ) {
		int d;
		scanf("%d", &d);
		while ( d -- ) {
			int x;
			scanf("%d", &x);
			e[i][x] = true;
		}
	}
	int nOut = 0;
	for ( int i = 1; i <= n; i ++ )
		if ( e[t][i] )
			for ( int j = 1; j <= n; j ++ )
				if ( j != t && i != t && i != j )
					if ( e[i][j] && !e[t][j] )
						out[nOut++] = j;
	sort(out, out + nOut);
	nOut = unique(out, out + nOut) - out;
	printf("%d\n", nOut);
	for ( int i = 0; i < nOut; i ++ )
		printf("%d ", out[i]);
}
