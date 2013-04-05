#include <cstdio>
//#include <cassert>
#include <algorithm>
#include <map>
using namespace std;
const int MOD = 65536;
const int kEleMax = MOD + 10;

map<int, int> cnt;

struct IndexTree {
	int ele[kEleMax];
	void add(int i, int v) {
		i += 5;
		for ( ; i < kEleMax; i += i & -i )
			ele[i] += v;
	}
	int sum(int i) {
		i += 5;
		int ret = 0;
		for ( ; i; i -= i & -i )
			ret += ele[i];
		return ret;
	}
};

struct AbstractDataStructure {
	int k, lb, rb;
	IndexTree idt;

	void add(int x) {
		idt.add(x, 1);
	}
	void del(int x, int v) {
		idt.add(x, -v);
	}
	int ask(int d) {
		d &= (1 << (k+1)) - 1;
		int ret = 0;
		int p = max(lb, (1<<k)-d),
			q = min(rb, min((1<<(k+1))-1-d, (1<<k)-1));

		if ( p <= q ) {
			ret += idt.sum(q);
			ret -= idt.sum(p - 1);
		}

		if ( !(d & (1 << k)) ) {
			p = max(lb, 1<<k);
			q = min(rb, (1<<(k+1))-1-d);
			if ( p <= q ) {
				ret += idt.sum(q);
				ret -= idt.sum(p - 1);
			}
		} else {
			p = max(lb, 1<<k);
			p = max(p, 3*(1<<k)-d);
			q = rb;
			if ( p <= q ) {
				ret += idt.sum(q);
				ret -= idt.sum(p - 1);
			}
		}
		return ret;
	}
} adt[16];

int main() {
	for ( int i = 0; i < 16; i ++ ) {
		adt[i].k = i;
		adt[i].lb = 0, adt[i].rb = (1<<(i+1))-1;
	}
	int nOprt = 0;
	scanf("%d", &nOprt);
	int delta = 0, realDelta = 0;
	while ( nOprt -- ) {
		static char cmd[10];
		scanf("%s", cmd);
		if ( cmd[0] == 'I' ) {
			int m;
			scanf("%d", &m);
			cnt.count(m-realDelta)?cnt[m-realDelta]++:cnt[m-realDelta]=1;
			m -= delta;
			m %= MOD;
			if ( m < 0 ) m += MOD;
			for ( int k = 0; k < 16; k ++ )
				adt[k].add(m & ((1 << (k + 1)) - 1));
		} else if ( cmd[0] == 'D' ) {
			int m;
			scanf("%d", &m);
			int y = m-realDelta, z = cnt.count(y)?cnt[y]:0;
			m -= delta;
			m %= MOD;
			if ( m < 0 ) m += MOD;
			for ( int k = 0; k < 16; k ++ )
				adt[k].del(m & ((1 << (k + 1)) - 1), z);
			if ( cnt.count(y) ) 
				cnt[y] = 0;
		} else if ( cmd[0] == 'A' ) {
			int m;
			scanf("%d", &m);
			realDelta += m;
			delta += m;
			delta %= MOD;
		} else {
			int k;
			scanf("%d", &k);
			int ans = 0;
			ans += adt[k].ask(delta);
			printf("%d\n", ans);
		}
	}
}
