#include <cstdio>
#include <algorithm>
using namespace std;
int a[111];
int n;

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int tot = 0;
	for ( int i=  0; i < n; i ++ ) {
		scanf("%d", &a[i]);
		tot += a[i];
	}
	sort(a, a + n);
	int sum = 0, ans = 0;
	for ( int i = n - 1; i >= 0; i -- ) {
		sum += a[i];
		if ( sum > tot - sum ) {
			ans = n - i;
			break;
		}
	}
	printf("%d\n", ans);
}
