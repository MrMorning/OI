#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, a[10000];
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ ) {
		int t;
		scanf("%d", &t);
		a[i] += 2 * t;
	}
	while ( m -- ) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		a[u] += w, a[v] += w; 
	}
	sort(a, a + n);
	int ans = 0;
	for ( int i = 0; i < n; i ++ ) {
		if ( i & 1 )
			ans += a[i];
		else
			ans -= a[i];
	}
	printf("%d\n", ans / 2);
}
