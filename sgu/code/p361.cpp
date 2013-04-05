#include <cstdio>
#include <cstring>

char testAns[333][333], ans[333][333];
int n, m;

int test(int d) {
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			testAns[i][j] = '0';
	int res = 0;
	for ( int i = d; i < n+m-1; i += 3 ) {
		for ( int x = 0; x < n; x ++ ) {
			int y = i-x;
			if ( 0 <= y && y < m ) {
				res++;
				testAns[x][y] = '#';
			}
		}
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int curBest = n*m;
	for ( int t = 0; t <= 2; t ++ ) {
		int tmp = test(t);
		if ( tmp < curBest ) {
			curBest = tmp;
			memcpy(ans, testAns, sizeof(ans));
		}
	}
	for ( int i = 0; i < n; i ++ )
		printf("%s\n", ans[i]);
}
