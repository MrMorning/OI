#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;

const int kNMax = 100010;
const int kEvMax = 5*kNMax;
const int kDisMax = 5*kNMax;

#define ADD 0
#define QUERY 1
struct Event {
	int type, w;
	ll x, y;
	bool operator< (const Event &E) const {
		return x < E.x || (x == E.x && type < E.type);
	}
} ev[kEvMax];

struct IndexTree {
	int ele[kDisMax];
	void add(int i, int val) {
		for ( ; i < kDisMax; i += i & -i )
			ele[i] += val;
	}
	int sum(int i) {
		int res = 0;
		for ( ; i; i -= i & -i )
			res += ele[i];
		return res;
	}
} idt;

struct Hut {
	int x, y, d;
} hut[kDisMax];

ll dis[kDisMax];
int nDis;
int nEv;
int n, bound;
int ans[kNMax], out[kNMax], nOut;

void addEv(int type, ll x, ll y, int w) {
	dis[nDis++] = y;
	ev[nEv].type = type, ev[nEv].x = x, ev[nEv].y = y, ev[nEv].w = w;
	nEv++;
}

void addRec(ll x1, ll y1, ll x2, ll y2) {
	addEv(ADD, x1, y1, +1);
	addEv(ADD, x1, y2+1, -1);
	addEv(ADD, x2+1, y1, -1);
	addEv(ADD, x2+1, y2+1, +1);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &bound);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d%d%d", &hut[i].x, &hut[i].y, &hut[i].d);
		addRec((ll)hut[i].x-hut[i].y-hut[i].d, (ll)hut[i].x+hut[i].y-hut[i].d,
				(ll)hut[i].x-hut[i].y+hut[i].d, (ll)hut[i].x+hut[i].y+hut[i].d);
	}
	for ( int i = 1; i <= n; i ++ ) 
		addEv(QUERY, (ll)hut[i].x-hut[i].y, (ll)hut[i].x+hut[i].y, i);

	sort(dis, dis+nDis);
	nDis = unique(dis, dis+nDis)-dis;

	sort(ev, ev+nEv);
	for ( int i = 0; i < nEv; i ++ ) {
		Event &E = ev[i];
		if ( E.type == ADD ) 
			idt.add(lower_bound(dis, dis+nDis, E.y)-dis+1, E.w);
		else
			ans[E.w] = idt.sum(lower_bound(dis, dis+nDis, E.y)-dis+1);
	}

	for ( int i = 1; i <= n; i ++ )
		if ( ans[i]-1 >= bound ) 
			out[nOut++] = i;
	printf("%d\n", nOut);
	for ( int i = 0; i < nOut; i ++ )
		printf("%d ", out[i]);
}
