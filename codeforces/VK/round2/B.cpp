
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

int N, K, H;
struct Stuff {
	int w, v, id;
	bool operator< (const Stuff &t) const {
		return w < t.w || (w == t.w && v < t.v);
	}
} stuff[100010];
int out[100010];

bool check(double lim) {
	int cnt = 0;
	for ( int i = 1; i <= N; i ++ ) {
		if ( H * (cnt + 1) <= lim * stuff[i].v ) 
			out[++ cnt] = stuff[i].id;
		if ( cnt == K )
			return true;
	}
	return false;
}

int main(){
	//freopen("t.in", "r", stdin);
	scanf("%d%d%d", &N, &K, &H);
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%d", &stuff[i].w);
		stuff[i].id = i;
	}
	for ( int i = 1; i <= N; i ++ )
		scanf("%d", &stuff[i].v);
	sort(stuff + 1, stuff + 1 + N);
	double lb = -1, rb = 1000000010;
	int times = 0;
	for ( double mid = (lb + rb) / 2; times < 100;
			mid = (lb + rb) / 2, times ++ ) {
		if ( check(mid) )
			rb = mid;
		else
			lb = mid;
	}
	check(rb);
	for ( int i = 1; i <= K; i ++ )
		printf("%d ", out[i]);
}
