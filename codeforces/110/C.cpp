#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
const int MOD = 1000000007;
char str[111];
int a[111];
int f[111][2600];
void init() {
	f[0][0] = 1;
	for ( int i = 0; i < 100; i ++ )
		for ( int j = 0; j <= 2500; j ++ )
			for ( int k = 0; k < 26; k ++ )
				f[i + 1][j + k] = (f[i + 1][j + k] + f[i][j]) % MOD;
}
void solve() {
	scanf("%s", str);
	int n = strlen(str);
	int sum = 0;
	for ( int i = 0; i < n; i ++ )
		sum += str[i] - 'a';
	int res = f[n][sum];
	res --;
	if ( res < 0 )
		res += MOD;
	printf("%d\n", res);
}

int main() {
	//freopen("t.in", "r", stdin);
	init();
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
