#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST-- ) {
		int n;
		scanf("%d", &n);
		int sum = 0, mi = 0x3f3f3f3f;
		for ( int i = 0; i < n; i ++ ) {
			int x;
			scanf("%d", &x);
			sum += x;
			mi = min(mi, x);
		}
		printf("%d\n", sum-mi*n);
	}
}
