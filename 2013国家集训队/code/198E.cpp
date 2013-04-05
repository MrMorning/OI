#include <cstdio>
#include <cassert>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;

const int kNMax = 250010;
const int kKeyMax = kNMax;

struct Grip {
	int x, y, p, r, d, m;
} grip[kNMax];

ll dis[kNMax];
int nDis;

ll calcDist(int i, int j) {
	return (ll)(grip[i].x-grip[j].x)*(grip[i].x-grip[j].x)
		+(ll)(grip[i].y-grip[j].y)*(grip[i].y-grip[j].y);
}

struct cmpMass {
	bool operator()(int i, int j) {
		return grip[i].m > grip[j].m || (grip[i].m == grip[j].m && i < j);
	}
};
set<int, cmpMass> idt[kNMax];
int que[kNMax], qt;
bool vis[kNMax];

int main() {
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d%d%d%d%d", &grip[0].x, &grip[0].y, &grip[0].p, &grip[0].r, &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d%d%d%d%d", &grip[i].x, &grip[i].y, &grip[i].m, &grip[i].p, &grip[i].r);
		dis[nDis++] = calcDist(0, i);
	}
	sort(dis, dis+nDis);
	nDis = unique(dis, dis+nDis)-dis;
	for ( int i = 0; i <= n; i ++ ) {
		grip[i].d = lower_bound(dis,dis+nDis,calcDist(0, i))-dis;
		grip[i].r = upper_bound(dis,dis+nDis,(ll)grip[i].r*grip[i].r)-dis-1;
	}
	for ( int i = 1; i <= n; i ++ ) {
		int key = grip[i].d, val = i;
		key += 5;
		for ( ;key < kKeyMax; key += key & -key ) 
			idt[key].insert(val);
	}
	que[qt++] = 0;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int key = grip[que[qh]].r, bnd = grip[que[qh]].p;
		grip[0].m = bnd;
		key += 5;
		for ( ; key; key -= key & -key ) {
			set<int>::iterator it = idt[key].lower_bound(0);
			while ( it != idt[key].end() ) {
				assert(grip[*it].m <= bnd);
				if ( !vis[*it] ) {
					vis[*it] = true;
					que[qt++] = *it;
				}
				idt[key].erase(it);
				it = idt[key].lower_bound(0);
			}
		}
	}
	printf("%d\n", qt-1);
}
