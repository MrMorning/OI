#include <cstdio>
#include <cstring>
typedef long long ll;
const int MOD = 1000000007;
int n, m;
bool vis[111][26];
int main() {
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ ) {
		static char str[111];
		scanf("%s", str);
		for ( int j = 0; j < m; j ++ )
			vis[j][str[j] - 'A'] = true;
	}
	int res = 1;
	for ( int i = 0; i < m; i ++ ) {
		int cnt = 0;
		for ( int j = 0; j < 26; j ++ )
			if ( vis[i][j] )
				cnt ++;
		res = (ll)res * cnt % MOD;
	}
	printf("%d\n", res);
}
