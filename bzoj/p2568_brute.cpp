#include <cstdio>
//#include <cassert>
#include <algorithm>
using namespace std;
int arr[500010], nArr;
int main() {
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	int nOprt = 0;
	scanf("%d", &nOprt);
	while ( nOprt -- ) {
		static char cmd[10];
		scanf("%s", cmd);
		if ( cmd[0] == 'I' ) {
			int m;
			scanf("%d", &m);
			arr[nArr++] = m;
		} else if ( cmd[0] == 'D' ) {
			int m;
			scanf("%d", &m);
			for ( int i = 0; i < nArr; i ++ ) {
				if ( arr[i] == m ) {
					swap(arr[--nArr], arr[i]);
					i--;
				}
			}
		} else if ( cmd[0] == 'A' ) {
			int m;
			scanf("%d", &m);
			for ( int i = 0; i <nArr; i ++ )
				arr[i] = arr[i]+m;
		} else { 
			int k;
			scanf("%d", &k);
			int ans = 0;
			for ( int i = 0; i < nArr; i ++ )
				ans += ((1<<k) & arr[i]) > 0;
			printf("%d\n", ans);
		}
	}
}
