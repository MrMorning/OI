
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
typedef pair<int, int> pair_t;
map<pair<pair_t, pair_t>, int> memo;
int count(int k, int l1, int r1, int l2, int r2) { //len=2^k-1
	pair<pair_t, pair_t> p = make_pair(make_pair(l1, r1), make_pair(l2, r2));

	if ( memo.count(p) )
		return memo[p];
	if ( l1 > r1 || l2 > r2 )
		return 0;
	if ( l1 > l2 ) {
		swap(l1, l2);
		swap(r1, r2);
	}
	int res = 0;
	res = max(res, min(r1, r2) - max(l1, l2) + 1);
	int mid = 1 << (k - 1);
	int t1 = l1, t2 = min(r1, mid - 1),
		t3 = max(mid + 1, l1) - mid, t4 = r1 - mid;
	int b1 = l2, b2 = min(r2, mid - 1),
		b3 = max(mid + 1, l2) - mid, b4 = r2 - mid;
	res = max(res, count(k - 1, t1, t2, b1, b2));
	res = max(res, count(k - 1, t1, t2, b3, b4));
	res = max(res, count(k - 1, t3, t4, b1, b2));
	res = max(res, count(k - 1, t3, t4, b3, b4));
	return memo[p] = res;
}

int main(){
	freopen("t.in", "r", stdin);
	int l1, r1, l2, r2;
	scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
	printf("%d\n", count(30, l1, r1, l2, r2));
}
