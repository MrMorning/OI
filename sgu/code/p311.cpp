#include <cstdio>
#include <cassert>
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
typedef long long ll;
const int LENGTH = 1000010;
namespace sgt {
	ll cnt[LENGTH * 3], sum[LENGTH * 3];
	bool tag[LENGTH * 3];

	inline void update(int i) {
		sum[i] = sum[i * 2] + sum[i * 2 + 1];
		cnt[i] = cnt[i * 2] + cnt[i * 2 + 1];
	}

	inline void mark(int i) {
		sum[i] = 0;
		cnt[i] = 0;
		tag[i] = true;
	}

	inline void pushDown(int i) {
		if ( tag[i] ) {
			mark(i * 2);
			mark(i * 2 + 1);
			tag[i] = false;
		}
	}
	void add(int i, int l, int r, int pos, int act) {
		if ( l == r ) {
			sum[i] += (ll)pos * act;
			cnt[i] += act;
			return;
		}
		pushDown(i);
		int mid = (l + r) / 2;
		if ( pos <= mid ) 
			add(i * 2, l, mid, pos, act);
		else
			add(i * 2 + 1, mid + 1, r, pos, act);
		update(i);
	}
	ll getSum(int i, int l, int r, ll k) {
		if ( l == r ) {
			assert(k <= cnt[i]);
			return (ll)k * l;
		}
		pushDown(i);
		int mid = (l + r) / 2;
		if ( cnt[i * 2] >= k )
			return getSum(i * 2, l, mid, k);
		else
			return sum[i * 2] + getSum(i * 2 + 1, mid + 1, r, k - cnt[i * 2]);
		update(i);
	}
	void clear(int i, int l, int r, ll k) {
		if ( l == r ) {
			sum[i] -= (ll)l * k;
			cnt[i] -= k;
			assert(sum[i] >= 0);
			assert(cnt[i] >= 0);
			return;
		}
		pushDown(i);
		int mid = (l + r) / 2;
		if ( cnt[i * 2] >= k ) 
			clear(i * 2, l, mid, k);
		else {
			clear(i * 2 + 1, mid + 1, r, k - cnt[i * 2]);
			mark(i * 2);
		}
		update(i);
	}
}
char ts[100];
int main() {
	freopen("t.in", "r", stdin);
	while ( gets(ts) ) {
		if ( ts[0] == 'A' ) {
			int n, c;
			sscanf(ts, "ARRIVE %d %d", &n, &c);
			sgt::add(1, 1, 1000000, c, n);
		} else {
			int n;
			ll t;
			sscanf(ts, "BUY %d " LL_FMT, &n, &t);
			if ( n > sgt::cnt[1] ) {
				puts("UNHAPPY");
				continue;
			}
			ll tmp = sgt::getSum(1, 1, 1000000, n);
			if ( tmp <= t ) {
				sgt::clear(1, 1, 1000000, n);
				puts("HAPPY");
			} else
				puts("UNHAPPY");
		}
	}
}
