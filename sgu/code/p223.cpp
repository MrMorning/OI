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
ll f[11][101][1 << 10];
int n, m;
ll curVal;

void dfs(int i, int j, int s, int lim, int st)
{
	if(j > m)
		return;
	f[i + 1][j][s] += curVal;
	for(int k = st; k < n; k ++)
		if((lim & (1 << k)) == 0)
			dfs(i, j + 1, s | (1 << k), (k == 0 ? (lim | 3) : (lim | (7 << (k - 1)))), k + 2);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int upperlim = 1 << n;
	f[0][0][0] = 1;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j <= m; j ++)
			for(int s = 0; s < upperlim; s ++)
				if(f[i][j][s])
				{
					int border = upperlim - 1;
					int cur = s | (border & (s << 1)) | (border & (s >> 1));
					curVal = f[i][j][s];
					dfs(i, j, 0, cur, 0);
				}
	ll res = 0;
	for(int s = 0; s < upperlim; s ++)
		res += f[n][m][s];
	cout << res;

}
