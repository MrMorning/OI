#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int kNMax = 1010;
struct Point { int x, y; } blackcell[kNMax];
int nBlackCell, n, m;
int rowblack[kNMax], colblack[kNMax];
bool black[kNMax][kNMax];
ll sqr(ll x) { return x * x; }

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		static char str[kNMax];
		scanf("%s", str+1);
		for ( int j = 1; j <= m; j ++ )
			if ( str[j] == 'X' ) {
				rowblack[i] = j;
				colblack[j] = i;
				blackcell[nBlackCell].x = i;
				blackcell[nBlackCell].y = j;
				nBlackCell++;
				black[i][j] = true;
			}
	}
	ll tot = 0;
	for ( int x1 = 1; x1 <= n; x1 ++ )
		for ( int x2 = 1; x2 <= n; x2 ++ ) 
			tot += (ll)m*m*abs(x1-x2);
	for ( int y1 = 1; y1 <= m; y1 ++ )
		for ( int y2 = 1; y2 <= m; y2 ++ )
			tot += (ll)n*n*abs(y1-y2);
	for ( int i = 0; i < nBlackCell; i ++ ) {
		int x1 = blackcell[i].x, y1 = blackcell[i].y;
		for ( int x2 = 1; x2 <= n; x2 ++ )
			tot -= 2LL*m*abs(x1-x2);
		for ( int y2 = 1; y2 <= m; y2 ++ ) 
			tot -= 2LL*n*abs(y1-y2);
	}
	for ( int i = 0; i < nBlackCell; i ++ )
		for ( int j = 0; j < nBlackCell; j ++ )
			tot += abs(blackcell[i].x-blackcell[j].x)+abs(blackcell[i].y-blackcell[j].y);

	for ( int i = 1; i <= n; i ++ ) 
		if ( rowblack[i] ) {
			ll cnt = rowblack[i]-1;
			for ( int j = i-1; j >= 1; j -- ) {
				if ( !rowblack[j] || rowblack[j] > rowblack[j+1] ) break;
				cnt += rowblack[j]-1;
			}
			for ( int j = i+1; j <= n; j ++ ) {
				if ( !rowblack[j] || rowblack[j] > rowblack[j-1] ) break;
				cnt += rowblack[j]-1;
			}
			tot += 2LL*2LL*cnt*(m-rowblack[i]);
		}
	for ( int i = 1; i <= m; i ++ )
		if ( colblack[i] ) {
			ll cnt = colblack[i]-1;
			for ( int j = i-1; j >= 1; j -- ) {
				if ( !colblack[j] || colblack[j] > colblack[j+1] ) break;
				cnt += colblack[j]-1;
			}
			for ( int j = i+1; j <= m; j ++ ) {
				if ( !colblack[j] || colblack[j] > colblack[j-1] ) break;
				cnt += colblack[j]-1;
			}
			tot += 2LL*2LL*cnt*(n-colblack[i]);
		}
	printf("%.10lf\n", (double)tot/sqr((ll)n*m-nBlackCell));
}
