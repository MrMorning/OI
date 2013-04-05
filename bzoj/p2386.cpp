#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 1000010;
int a[N_MAX], n;
ll s[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	for ( int i = 1; i <= n; i ++ )
		s[i] = s[i - 1] + a[i];
	for ( int i = 0; i <= n; i ++ )
		if ( s[i] + n - i >= s[n] - s[i] ) {
			printf("%d\n", n - i);
			return 0;
		}
}
