
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

int n, m, x, y;
int a[100010], b[100010];
vector<pair<int, int> > out;
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &n, &m, &x, &y);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	for ( int j = 1; j <= m; j ++ ) 
		scanf("%d", &b[j]);
	int q = 1;
	for ( int i = 1; i <= n; i ++ ) {
		while( q <= m && a[i] - x > b[q] )
			q ++;
		if ( q == m + 1 )
			break;
		if ( a[i] + y < b[q] )
			continue;
		out.push_back(make_pair(i, q));
		q ++;
	}
	printf("%d\n", (int)out.size());
	for ( int i = 0; i < (int)out.size(); i ++ )
		printf("%d %d\n", out[i].first, out[i].second);
}
