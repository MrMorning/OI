#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kLenMax = 300010;
const int kInf = 0x3f3f3f3f;

struct Info {
	int val[2], cnt[2];
	bool e;
	Info(bool _e=false) { e=_e; }
	void mark(int tag) { 
		assert(e);
		val[0] += tag; val[1] += tag; 
	}
	void set(int v) {
		e = true;
		val[0] = v, cnt[0] = 1;
		val[1] = kInf, cnt[1] = 0;
	}
};

Info operator+ (const Info &I1, const Info &I2) {
	if ( !I1.e ) return I2;
	if ( !I2.e ) return I1;
	static Info res;
	res.e = true;
	if ( I1.val[0] == I2.val[0] ) {
		res.val[0] = I1.val[0];
		res.cnt[0] = I1.cnt[0] + I2.cnt[0];
		res.val[1] = min(I1.val[1], I2.val[1]);
		if ( I1.val[1] == I2.val[1] ) res.cnt[1] = I1.cnt[1]+I2.cnt[1];
		else res.cnt[1] = I1.val[1]<I2.val[1]?I1.cnt[1]:I2.cnt[1];
	} else if ( I1.val[0] < I2.val[0] ) {
		res.val[0] = I1.val[0]; res.cnt[0] = I1.cnt[0];
		res.val[1] = min(I1.val[1], I2.val[0]);
		if ( I1.val[1] == I2.val[0] ) res.cnt[1] = I1.cnt[1]+I2.cnt[0];
		else res.cnt[1] = I1.val[1]<I2.val[0]?I1.cnt[1]:I2.cnt[0];
	} else {
		res.val[0] = I2.val[0]; res.cnt[0] = I2.cnt[0];
		res.val[1] = min(I1.val[0], I2.val[1]);
		if ( I1.val[0] == I2.val[1] ) res.cnt[1] = I1.cnt[0]+I2.cnt[1];
		else res.cnt[1] = I1.val[0]<I2.val[1]?I1.cnt[0]:I2.cnt[1];
	}
/*	static int arr[4];
	arr[0] = I1.val[0], arr[1] = I1.val[1], arr[2] = I2.val[0], arr[3] = I2.val[1];
	sort(arr, arr + 4);
	unique(arr, arr+4);
	res.val[0] = arr[0], res.val[1] = arr[1];
	res.cnt[0] = res.cnt[1] = 0;
	for ( int t = 0; t <= 1; t ++ ) {
		if ( I1.val[t] == arr[0] ) res.cnt[0] += I1.cnt[t];
		if ( I1.val[t] == arr[1] ) res.cnt[1] += I1.cnt[t];
		if ( I2.val[t] == arr[0] ) res.cnt[0] += I2.cnt[t];
		if ( I2.val[t] == arr[1] ) res.cnt[1] += I2.cnt[t];
	}
	*/
	return res;
 }

struct Node {
	int l, r, tag;
	Info info;
} node[kLenMax*4];
void update(int i) {
	node[i].info = node[i*2].info + node[i*2+1].info;
}
void mark(int i, int tag) {
	node[i].tag += tag;
	node[i].info.mark(tag);
}
void pushDown(int i) {
	if ( node[i].tag != 0 ) {
		mark(i*2, node[i].tag);
		mark(i*2+1, node[i].tag);
		node[i].tag = 0;
	}
}
void build(int i, int l, int r) {
	node[i].l = l, node[i].r = r;
	node[i].tag = 0;
	if ( l == r ) return;
	int mid = (l + r) / 2;
	build(i*2, l, mid); build(i*2+1, mid+1, r);
}
Info ask(int i, int l, int r) {
	if ( node[i].l > r || node[i].r < l ) return Info(false);
	if ( l <= node[i].l && node[i].r <= r ) return node[i].info;
	pushDown(i);
	Info res = ask(i*2,l,r)+ask(i*2+1,l,r);
	update(i);
	return res;
}
void set(int p, int val) {
	int cur = 1;
	while ( node[cur].l != node[cur].r ) {
		pushDown(cur);
		int mid = (node[cur].l+node[cur].r)/2;
		if ( p <= mid ) cur *= 2;
		else cur = cur*2+1;
	}
	node[cur].info.set(val);
	for ( cur >>= 1; cur; cur >>= 1 ) 
		update(cur);
}
void add(int i, int l, int r, int val) {
	if ( node[i].l > r || node[i].r < l ) return;
	if ( l <= node[i].l && node[i].r <= r ) {
		mark(i, val);
		return;
	}
	pushDown(i);
	add(i*2,l,r,val); add(i*2+1,l,r,val);
	update(i);
}
void pushAll(int i) {
	if ( node[i].l == node[i].r ) return;
	pushDown(i);
	pushAll(i*2); pushAll(i*2+1);
	update(i);
}

int n, a[kLenMax], p[kLenMax];

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &a[i]);
		p[a[i]] = i;
	}
	build(1, 1, n);
	ll ans = 0;
	for ( int l = n; l >= 1; l -- ) {
		int k1, k2, x1 = a[p[l]-1], x2 = a[p[l]+1];
		if ( x1 < l && x2 < l ) k1 = k2 = n;
		else if ( x1 > l && x2 < l ) k1 = x1-1, k2 = n;
		else if ( x1 < l && x2 > l ) k1 = x2-1, k2 = n;
		else k1 = min(x1, x2)-1, k2 = max(x1, x2)-1;
		set(l, 1);
		if ( l+1 <= k1 ) {
			add(1, l+1, k1, 1);
		}
		if ( k2+1 <= n ) {
			add(1, k2+1, n, -1);
		}

		Info res = ask(1, l, n);
		assert(res.val[0]==1);
		ans += res.cnt[0];
		if ( res.val[1] == 2) ans += res.cnt[1];
	}
	cout << ans - n;
}
