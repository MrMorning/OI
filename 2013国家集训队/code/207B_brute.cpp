#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, a[250010], f[250010];
typedef long long ll;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &a[n-i+1]);
	ll ans = 0;
	for ( int i = 0; i < n; i ++ ) {
		f[n] = 0;
		for ( int j = n-1; j >= 1; j -- ) {
			f[j] = 0x3f3f3f3f;
			for ( int k = j; k <= min(n, j+a[j]); k++)
				f[j] = min(f[j], f[k]+1);
		}
		ans += f[1];
		int tmp = a[1];
		memmove(a+1, a+2, sizeof(int)*(n-1));
		a[n] = tmp;
	}
	printf("%lld\n", ans);
}
