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
ll f[2][52][1 << 10][1 << 10];
int n, m;
ll curVal;

void dfs(int i, int j, int t, int s, int lim, int st)
{
	if(j > m)
		return;
	f[(i + 1) & 1][j][t][s] += curVal;
	for(int k = st; k < n; k ++)
		if((lim & (1 << k)) == 0)
			dfs(i, j + 1, t, s | (1 << k), lim, k + 1);
}

int main()
{
	freopen("t.out", "w", stdout);
	//scanf("%d%d", &n, &m);
	for(n = 1; n <= 10; n ++)
	{
		printf("{");
		m = min(50, n * n); 
		{
			fprintf(stderr, "%d %d\n", n, m);
			int upperlim = 1 << n;
			memset(f, 0, sizeof(f));
			f[0][0][0][0] = 1;
			for(int i = 0; i < n; i ++)
			{
				memset(f[!(i & 1)], 0, sizeof(f[!(i & 1)]));
				for(int j = 0; j <= m; j ++)
					for(int s = 0; s < upperlim; s ++)
						for(int t = 0; t < upperlim; t ++)
							if(f[i & 1][j][s][t])
							{
								int border = upperlim - 1;
								int cur = (border & (s << 1)) | (border & (s >> 1)) | (border & (t << 2)) | (border & (t >> 2));
								curVal = f[i & 1][j][s][t];
								dfs(i, j, t, 0, cur, 0);
							}
			}
			for(int c = 0; c <= min(50, n * n); c ++)
			{
				ll res = 0;
				for(int s = 0; s < upperlim; s ++)
					for(int t = 0; t < upperlim; t ++)
						res += f[n & 1][c][s][t];
				cout << res << "LL, ";
			}
			for(int c = min(50, n * n) + 1; c <= 100; c ++)
				printf("0LL%c ", c == 100 ? '}' : ',');
		}
		printf(", ");
	}
}
