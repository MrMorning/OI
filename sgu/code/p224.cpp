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
int n, m, border;
int ans;
void dfs(int i, int j, int a, int b, int c)
{
	if(i == n + 1)
	{
		if(j == m)
			ans ++;
		return;
	}
	dfs(i + 1, j, border & (a << 1), b, c >> 1);
	int tmp = border & (~a & ~b & ~c);
	while(tmp)
	{
		int pos = tmp & (~tmp + 1);
		tmp -= pos;
		dfs(i + 1, j + 1, border & ((a | pos) << 1), b | pos, (c | pos) >> 1);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	if(m > n)
	{
		printf("0\n");
		return 0;
	}
	border = (1 << n) - 1;
	dfs(1, 0, 0, 0, 0);
	cout << ans;
}

