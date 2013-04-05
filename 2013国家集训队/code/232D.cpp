#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

#define ELE 0
#define ASK 1

const int kLenMax = 440000;
const int kEventMax = 1100000;

struct Event {
	int pos, l, r, des, type, key, flag;

	Event(){}
	Event(int tt, int ll, int rr, int kk, int ff, int dd):
   		type(tt), l(ll), r(rr), key(kk), flag(ff), des(dd){}
	Event(int tt, int pp, int kk):
		type(tt), pos(pp), key(kk){}

	bool operator< (const Event &T) const {
		return key < T.key || (key == T.key && type < T.type);
	}
} ev[kEventMax];
int nEv = 0;

struct IndexTree {
	int ele[kLenMax];
	void add(int i, int v) {
		i += 5;
		for ( ; i < kLenMax; i += i & -i )
			ele[i] += v;
	}
	int sum(int i) {
		i += 5;
		int res = 0;
		for ( ; i; i -= i & -i )
			res += ele[i];
		return res;
	}
} idt;

int rank[kLenMax], sa[kLenMax], height[kLenMax];
int st[20][kLenMax], log2[kLenMax];

void countSort(int *x, int *y, int n) {
	static int w[kLenMax];
	memset(w, 0, sizeof(w));
	for ( int i = 0; i < n; i ++ )
		w[x[y[i]]]++;
	for ( int i = 0; i < kLenMax - 1; i ++ )
		w[i+1] += w[i];
	for ( int i = n-1; i >= 0; i -- )
		sa[-- w[x[y[i]]]] = y[i];
}

bool isEqual(int *x, int i, int j, int l) {
	return x[i] == x[j] && x[i+l] == x[j+l];
}

void initSA(int *s, int n) {
	static int _x[kLenMax], _y[kLenMax];

	int *x = _x, *y = _y;
	for ( int i = 0; i < n; i ++ )
		x[i] = s[i], y[i] = i;
	countSort(x, y, n);

	for ( int p = 0, len = 1, i = 0; p < n; len *= 2) {
		for ( p = 0, i = n-len; i < n; i ++ )
			y[p++] = i;
		for ( i = 0; i < n; i ++ ) 
			if ( sa[i] >= len ) 
				y[p++] = sa[i] - len;
		countSort(x, y, n);
		swap(x, y);
		for ( p = 1, i = 1, x[sa[0]] = 0; i < n; i ++ )
			x[sa[i]] = isEqual(y, sa[i], sa[i-1], len) ? p-1 : p++;
	}

	for ( int i = 0; i< n; i ++ )
		rank[sa[i]] = i;

	for ( int k = 0, i = 0; i < n; height[rank[i++]] = k ) 
		if ( rank[i] == n-1 ) k = 0;
		else for ( k ? k-- : 0; s[i + k] == s[sa[rank[i] + 1]+k]; k++ );
}

void initST(int n) {
	for ( int i = 0; (1 << i) <= n; i ++ )
		log2[1<<i] = i;
	for ( int i = 2; i <= n; i ++ )
		if ( !log2[i] ) log2[i] = log2[i-1];
	for ( int i = 0; i < n; i ++ )
		st[0][i] = height[i];
	for ( int k = 1; (1 << k) <= n; k ++ )
		for ( int i = 0; i < n; i ++ ) {
			st[k][i] = st[k-1][i];
			int t = i+(1 << (k-1));
			if ( t < n && st[k-1][t] < st[k][i] )
				st[k][i] = st[k-1][t];
		}
}

int getRMQ(int l, int r) {
	int k = r - l + 1, z = log2[k];
	return min(st[z][l], st[z][r-(1<<z)+1]);
}

int getLCP(int i, int j) {
	assert(i != j);
	if ( i > j ) swap(i, j);
	return getRMQ(i, j-1);
}

pair<int, int> askRange(int pos, int len, int n) {
	pair<int, int> res;
	int l = -1, r = rank[pos];
	for ( int mid = (l + r) / 2; l < r - 1; mid = (l + r) / 2 ) {
		if ( getLCP(mid, rank[pos]) >= len )
			r = mid;
		else
			l = mid;
	}
	res.first = r;
	l = rank[pos], r = n;
	for ( int mid = (l + r) / 2; l < r - 1; mid = (l + r) / 2 ) {
		if ( getLCP(rank[pos], mid) >= len )
			l = mid;
		else
			r = mid;
	}
	res.second = l;
	return res;
}

int n;
int dis[kLenMax], nDis;
int a[kLenMax], b[kLenMax], s[kLenMax];
int nQuest, ans[kLenMax];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d", &a[i]);
	for ( int i = 0; i < n-1; i ++ ) {
		b[i] = a[i] - a[i+1];
		b[n-1+i] = -b[i];
		dis[nDis++] = b[i];
		dis[nDis++] = b[n-1+i];
	}
	sort(dis, dis + nDis);
	nDis = unique(dis, dis + nDis) - dis;
	for ( int i = 0; i < 2*n-2; i ++ )
		b[i] = lower_bound(dis, dis + nDis, b[i]) - dis + 2;
	memcpy(s, b, (n-1) * sizeof(b[0]));
	s[n-1] = 1;
	memcpy(s+n, b+(n-1), (n-1) * sizeof(b[0]));

	initSA(s, 2*(n-1)+1);
	initST(2*(n-1));

	scanf("%d", &nQuest);
	for ( int i = 0; i < nQuest; i ++ ) {
		int l, r;
		scanf("%d%d", &l, &r);
		if ( l == r ) {
			ans[i] = n-1;
			continue;
		}
		l --, r -= 2;
		pair<int, int> range = askRange(l+n, r-l+1, 2*n-1);
		if ( n-2 >= r+2 ) {
			ev[nEv++] = Event(ASK, range.first, range.second, n-2, 1, i);
			ev[nEv++] = Event(ASK, range.first, range.second, r+1, -1, i);
		}
		if ( l-(r-l+1)-1 >= 0 )
			ev[nEv++] = Event(ASK, range.first, range.second, l-(r-l+1)-1, 1, i);
	}

	for ( int i = 0; i < 2*n-1; i ++ )
		ev[nEv++] = Event(ELE, i, sa[i]);
	sort(ev, ev + nEv);
	for ( int i = 0; i < nEv; i ++ ) {
		Event &T = ev[i];
		if ( T.type == ASK ) {
			int res = idt.sum(T.r) - idt.sum(T.l-1);
			ans[T.des] += T.flag * res;
		} else {
			idt.add(T.pos, 1);
		}
	}
	for ( int i = 0; i < nQuest; i ++ )
		printf("%d\n", ans[i]);
}
