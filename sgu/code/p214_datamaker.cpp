
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
int n, m, t, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &t, &seed);
	srand(seed);
	for(int i = 0; i < n; i ++)
		printf("%c", i + ' ' + 1);
	printf("\n");
	REP(i, m)
		printf("%c", rand() % n + ' ' + 1);
	printf("\n");
	REP(i, t)
		printf("%c", rand() % n + ' ' + 1);
	printf("\n");
	REP(i, n)
	{
		REP(j, n)
		printf("%d ", rand() % 1000 + 1);
	printf("\n");
	}
}
