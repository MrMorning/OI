#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n, a[111], b[111];
char s[222];
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", s);
	for ( int i = 0; i < n; i ++ )
		a[i] = s[i] - '0';
	for ( int i = n; i < 2 * n; i ++ )
		b[i - n] = s[i] - '0';
	sort(a, a + n);
	sort(b, b + n);
	if ( a[n - 1] > b[n - 1] ) {
		for ( int i = 0; i < n; i ++ )
			if ( a[i] <= b[i] ) {
				printf("NO\n");
				return 0;
			}
	} else if ( a[n - 1] < b[n - 1] ) {
		for ( int i = 0; i < n; i ++ )
			if ( a[i] >= b[i] ) {
				printf("NO\n");
				return 0;
			}
	} else if ( a[n - 1] == b[n - 1] ) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
}
