#include <cstdio>
#include <cassert>
#include <algorithm>
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
using namespace std;

const ll kInf = 0x3f3f3f3f;
const ll kNMax = 100010;
const ll kDisMax = kNMax*7;

ll dis[kDisMax], nDis;
ll n, g, r, p, q, L[kNMax], t[kNMax], s[kNMax];
ll ans[kNMax], S[kNMax], f[kNMax];

ll fetch(ll x) {
	ll res = lower_bound(dis,dis+nDis,x)-dis;
	if(!(dis[res]==x))
		assert(0);
	return res;
}

void addDis(ll x) {
	if ( 0 <= x && x < p )
		dis[nDis++] = x;
}

struct Node {
	ll l, r, val;
} node[kDisMax*4];

void update(ll i) {
	node[i].val = min(node[i*2].val, node[i*2+1].val);
}

void build(ll i, ll l, ll r) {
	node[i].l = l, node[i].r = r;
	node[i].val = kInf;
	if ( l == r ) return;
	ll mid = (l + r) / 2;
	build(i*2, l, mid);
	build(i*2+1, mid+1, r);
}

ll askMin(ll i, ll l, ll r) {
	if ( node[i].l > r || node[i].r < l ) return kInf;
	if ( l <= node[i].l && node[i].r <= r ) 
		return node[i].val;
	return min(askMin(i*2,l,r), askMin(i*2+1,l,r));
}

ll askMin(ll l, ll r) {
	if ( l < 0 ) l = 0;
	if ( r >= p ) r = p-1;
	if ( l > r ) return kInf;
	l = fetch(l); r = fetch(r);
	if ( l > r || l < 0 || r >= nDis ) return kInf;
	return askMin(1, l, r);
}

void insert(ll p, ll val) {
	p = fetch(p);
	ll cur = 1;
	while ( 1 ) {
		if ( node[cur].l == node[cur].r ) break;
		ll mid = (node[cur].l + node[cur].r) / 2;
		if ( p <= mid ) 
			cur = cur * 2;
		else cur = cur * 2 + 1;
	}
	node[cur].val = val;
	for ( cur >>= 1; cur; cur >>= 1 )
		update(cur);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf(LL_FMT LL_FMT LL_FMT, &n, &g, &r);
	p = g+r;
	for ( ll i = 1; i <= n+1; i ++ ) {
		scanf(LL_FMT, &L[i]);
		s[i] = (L[i]+s[i-1]) % p;
		S[i] = S[i-1]+L[i];
	}
	scanf(LL_FMT, &q);
	for ( ll i = 1; i <= q; i ++ )
		scanf(LL_FMT, &t[i]);
	addDis(0);
	addDis(p-1);
	for ( ll i = 1; i <= n; i ++ ) {
		addDis(s[i]);
		addDis(s[i]-1);
		addDis(g+s[i]-p);
		addDis(g+s[i]);
	}
	for ( ll i = 1; i <= q; i ++ ) {
		addDis(g-t[i]%p);
		addDis(p-t[i]%p-1);
		addDis(g+p-t[i]%p);
	}
	sort(dis, dis+nDis);
	nDis = unique(dis, dis+nDis)-dis;

	build(1, 0, nDis-1);
	for ( ll i = n; i >= 1; i -- ) {
		ll k = min(askMin(g+s[i]-p, s[i]-1), askMin(g+s[i], p-1));
		if ( k == kInf ) 
			f[i] = S[n+1]-S[i];
		else
			f[i] = S[k]-S[i]+(p-(s[k]-s[i]+p)%p)+f[k];
		insert(s[i], i);
	}
	for ( ll i = 1; i <= q; i ++ ) {
		ll k = min(askMin(g-t[i]%p,p-t[i]%p-1), askMin(g+p-t[i]%p, p-1));
		if ( k == kInf )
			ans[i] = t[i]+S[n+1];
		else
			ans[i] = t[i]+S[k]+(p-(t[i]%p+s[k])%p)+f[k];
	}
	for ( ll i = 1; i <= q; i ++ )
		printf(LL_FMT "\n", ans[i]);
}
