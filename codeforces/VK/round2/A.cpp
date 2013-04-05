// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}

const int MOD = 1000000007;
char str1[5010], str2[5010];
int f[5010][5010], g[5010][5010];

int main(){
//	freopen("t.in", "r", stdin);
	scanf("%s%s", str1 + 1, str2 + 1);
	int n = strlen(str1 + 1);
	int m = strlen(str2 + 1);
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			if ( str1[i] == str2[j] ) 
				f[i][j] = (1 + g[i - 1][j - 1]) % MOD;
			res = (res + f[i][j]) % MOD;
			g[i][j] = (g[i][j - 1] + f[i][j]) % MOD;
		}
	cout << res;
}
