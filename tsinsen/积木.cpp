#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, c, f[111][111], h[111];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &c);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &h[i]);
	memset(f, 0x3f, sizeof(f));
	for ( int i = 0; i + h[0] <= 100; i ++ )
		f[0][i] = i * i;
	for ( int i = 1; i < n; i ++ ) 
		for ( int j = 0; j + h[i] <= 100; j ++ ) {
			for ( int k = 0; k + h[i - 1] <= 100; k ++ )
				if ( (h[i] <= h[i - 1] && h[i] + j <= h[i - 1] + k)
						|| (h[i] >= h[i - 1] && h[i] + j >= h[i - 1] + k))
					f[i][j] = min(f[i][j], f[i - 1][k] + c * abs(h[i] + j - (h[i - 1] + k)) + j * j);
		}
	int res = inf;
	for ( int j = 0; j + h[n - 1] <= 100; j ++ )
		res = min(res, f[n - 1][j]);
	printf("%d\n", res);
}
