#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, color[11111];
bool vis[11111];
int main() {
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		memset(vis, 0, sizeof(vis));
		for ( int j = 1; j < n; j ++ )
			if ( i % j == 0 ) 
				vis[color[j]] = true;
		for ( int j = 1; ; j ++ ) {
			if ( !vis[j] ) {
				color[i] = j;
				break;
			}
		}
	}
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		res = max(res, color[i]);
	printf("%d\n", res);
	for ( int i = 1; i <= n; i ++ )
		printf("%d ", color[i]);
}
