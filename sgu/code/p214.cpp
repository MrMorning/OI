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

int f[2010][2010], g[2010][2010];
int minD[2][210], minG[2][210];
vector<int> ans[2];
char sigma[210], lamda[2010], mu[2010];
int d[210][210];
int a[2010], b[2010];
int z, n, m;
map<char, int> M;

void trail(int i, int j)
{
	if(i == 0 && j == 0)
		return;
	if(g[i][j] == 0)
	{
		trail(i - 1, j - 1);
		ans[0].PB(a[i - 1]);
		ans[1].PB(b[j - 1]);
	}
	else if(g[i][j] == 1)
	{
		trail(i - 1, j);
		ans[0].PB(a[i - 1]);
		ans[1].PB(minG[0][a[i - 1]]);
	}
	else
	{
		trail(i, j - 1);
		ans[0].PB(minG[1][b[j - 1]]);
		ans[1].PB(b[j - 1]);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s", sigma);
	z = strlen(sigma);
	REP(i, z)
		M[sigma[i]] = i;
	scanf("%s%s", lamda, mu);
	n = strlen(lamda);
	m = strlen(mu);
	REP(i, n)
		a[i] = M[lamda[i]];
	REP(i, m)
		b[i] = M[mu[i]];
	REP(i, z)
		REP(j, z)
			scanf("%d", &d[i][j]);
	memset(minD, 0x3f, sizeof(minD));
	REP(i, z)
		REP(j, z)
		{
			if(d[i][j] < minD[0][i])
				minD[0][i] = d[i][j], minG[0][i] = j;
			if(d[i][j] < minD[1][j])
				minD[1][j] = d[i][j], minG[1][j] = i;
		}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	REP(i, n + 1)
		REP(j, m + 1)
		{
			if(i + 1 <= n && j + 1 <= m)
				if(f[i + 1][j + 1] > f[i][j] + d[a[i]][b[j]])
				{
					f[i + 1][j + 1] = f[i][j] + d[a[i]][b[j]];
					g[i + 1][j + 1] = 0;
				}
			if(i + 1 <= n)
				if(f[i + 1][j] > f[i][j] + minD[0][a[i]])
				{
					f[i + 1][j] = f[i][j] + minD[0][a[i]];
					g[i + 1][j] = 1;
				}
			if(j + 1 <= m)
				if(f[i][j + 1] > f[i][j] + minD[1][b[j]])
				{
					f[i][j + 1] = f[i][j] + minD[1][b[j]];
					g[i][j + 1] = 2;
				}
		}
	printf("%d\n", f[n][m]);
	trail(n, m);
	REP(t, 2)
	{
		REP(i, (int)ans[t].size())
			printf("%c", sigma[ans[t][i]]);
		printf("\n");
	}
	int res = 0;
	REP(i, (int)ans[0].size())
		res += d[ans[0][i]][ans[1][i]];
	assert(res == f[n][m]);
}
