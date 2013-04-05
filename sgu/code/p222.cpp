
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define FOR(I, A, B)	for(int I = (A); I < (B); I ++)
#define REP(I, N)	FOR(I, 0, N)
#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
#define ALL(I) (I).begin(), (I).end()
#define PB(X) push_back(X)

using namespace std;

typedef long long ll;

// }}}
ll f[15][15];
int main()
{
	freopen("t.in", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	f[0][0] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= n; j ++)
		{
			f[i][j] += f[i - 1][j];
			if(j)
				f[i][j] += (n - j + 1) * f[i - 1][j - 1];
		}
	if(k > n)
		cout << 0;
	else
		cout << f[n][k];
}
