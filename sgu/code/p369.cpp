#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const int kNMax = 400010;

struct DisjointSet {
	int p[kNMax];
	int find(int x) { 
		static int stk[kNMax];
		int top = 0;
		int cur = x;
		while ( p[cur] != cur ) {
			stk[top++] = cur;
			cur = p[cur];
		}
		while ( top )
			p[stk[--top]] = cur;
		return cur;
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		p[x] = y;
	}
} ds;

int x[kNMax], y[kNMax], disX[kNMax], disY[kNMax];
int n, sumX[kNMax], sumY[kNMax], nDisX, nDisY;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d%d", &x[i], &y[i]);
		disX[nDisX++] = x[i];
		disY[nDisY++] = y[i];
	}
	sort(disX, disX+nDisX);
	sort(disY, disY+nDisY);
	nDisX = unique(disX, disX+nDisX)-disX;
	nDisY = unique(disY, disY+nDisY)-disY;
	int tot = nDisX + nDisY;
	for ( int i = 1; i <= tot; i ++ )
		ds.p[i] = i;
	for ( int i = 1; i <= n; i ++ ) {
		int tx = lower_bound(disX,disX+nDisX,x[i])-disX,
			ty = lower_bound(disY,disY+nDisY,y[i])-disY;
		ds.merge(tx+1, ty+nDisX+1);
	}
	for ( int i = 1; i <= nDisX; i ++ )
		sumX[ds.find(i)] ++;
	for ( int i = 1; i <= nDisY; i ++ )
		sumY[ds.find(nDisX+i)]++;
	ll ans = 0;
	for ( int i = 1; i <= tot; i ++ )
		if ( ds.find(i) == i )
			ans += (ll)sumX[i]*sumY[i];
	printf(LL_FMT "\n", ans);
}
