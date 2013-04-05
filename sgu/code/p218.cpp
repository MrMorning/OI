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
const int oo = 0x3f3f3f3f;
bool vis[500];
int match[500];
int n;
int w[500][500];
int ans[500];

bool aug(int u, int upperlim)
{
	REP(v, n)
		if(w[u][v] <= upperlim)
			if(!vis[v])
			{
				vis[v] = true;
				if(match[v] == -1 || aug(match[v], upperlim))
				{
					match[v] = u;
					return true;
				}
			}
	return false;
}
bool check(int upperlim)
{
	memset(match, -1, sizeof(match));
	REP(i, n)
	{
		memset(vis, 0, sizeof(vis));
		if(!aug(i, upperlim))
			return false;
	}
	return true;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int maxW = -oo, minW = oo;
	REP(i, n)
		REP(j, n)
		{
			scanf("%d", &w[i][j]);
			maxW = max(maxW, w[i][j]);
			minW = min(minW, w[i][j]);
		}
	int lb = minW - 1, rb = maxW;
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(check(mid))
			rb = mid;
		else
			lb = mid;
	check(rb);
	printf("%d\n", rb);
	REP(i, n)
		ans[match[i]] = i;
	REP(i, n)
		printf("%d %d\n", i + 1, ans[i] + 1);
}
