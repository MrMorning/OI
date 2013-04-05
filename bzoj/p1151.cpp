#include <cstdio>
#include <vector>
#include <cstring>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++ )
using namespace std;

vector<pair<int, int> > vec[10010];
int nFence, nChild;
int f[2][1 << 4][1 << 4];

void upd(int &x, int y) {
	if ( y > x )
		x = y;
}

int calc(int pos, int msk) {
	int res = 0;
	FOREACH(it, vec[pos]) 
		if ( (it->first | msk) || (it->second | (~msk)) )
			res ++;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nFence, &nChild);
	while ( nChild -- ) {
		int E, F, L;
		scanf("%d%d%d", &E, &F, &L);
		E --;
		E = (E + 4) % nFence;
		int loveMsk = 0, hateMsk = 0;
		while ( F -- ) {
			int p;
			scanf("%d", &p);
			p --;
			hateMsk |= 1 << ((E - p + nFence) % nFence);
		}
		while ( L -- ) {
			int p;
			scanf("%d", &p);
			p --;
			loveMsk |= 1 << ((E - p + nFence) % nFence);
		}

		vec[E].push_back(make_pair(loveMsk, hateMsk));
	}

	int upperLim = 1 << 4;
	memset(f, -0x3f, sizeof(f));
	for ( int s = 0; s < upperLim; s ++ )
		f[0][s][s] = 0;
	for ( int i = 0; i < nFence; i ++ ) {
		memset(f[(i + 1) & 1], -0x3f, sizeof(f[0]));
		for ( int s0 = 0; s0 < upperLim; s0 ++ ) 
			for ( int s1 = 0; s1 < upperLim; s1 ++ ) 
				if ( f[i & 1][s0][s1] >= 0 ) {
					int ns = ((s1 << 1) | 1) & (upperLim - 1);
					upd(f[(i + 1) & 1][s0][ns], f[i & 1][s0][s1] + calc(i, ns));

					ns = (s1 << 1) & (upperLim - 1);
					upd(f[(i + 1) & 1][s0][ns], f[i & 1][s0][s1] + calc(i, ns));
				}
	}
	int ans = 0;
	for ( int s = 0; s < upperLim; s ++ )
		upd(ans, f[nFence & 1][s][s]);
	printf("%d\n", ans);
}
