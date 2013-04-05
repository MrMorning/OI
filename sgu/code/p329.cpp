#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int kHashMax = 200000;
const int kCodeMax = 99991;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

inline int getbit(int s, int i) {
	return (s & (1 << i)) > 0;
}
inline int setbit(int s, int i) {
	return s | (1 << i);
}

struct HashKey {
	int s, cnt[4];
	HashKey(){}
	HashKey(int _s, int c0, int c1, int c2, int c3) {
		s = _s;
		cnt[0] = c0, cnt[1] = c1, cnt[2] = c2, cnt[3] = c3;
	}
	int hash() const{
		int res = 0;
		for ( int i = 0; i < 4; i ++ ) 
			res = res * 26 + cnt[i];
		res = res * 26 + s;
		return res % kCodeMax;
	}
	bool operator== (const HashKey &T) const {
		return s == T.s && cnt[0] == T.cnt[0]
			&& cnt[1] == T.cnt[1] && cnt[2] == T.cnt[2]
			&& cnt[3] == T.cnt[3];
	}
};
struct HashMap {
	pair<HashKey, ll> ele[kHashMax];
	int begin[kCodeMax], next[kHashMax];
	int size;
	void clear() {
		memset(begin, -1, sizeof(begin));
		size = 0;
	}
	ll &get(const HashKey &key) {
		int code = key.hash();
		for ( int e = begin[code]; e != -1; e = next[e] )
			if ( ele[e].first == key )
				return ele[e].second;
		ele[size] = make_pair(key, 0);
		next[size] = begin[code];
		begin[code] = size;
		return ele[size ++].second;
	}
} HM[2], *src, *des;

int tot[4], rem[4], n;

void expand(int i, int lev, int ups, int pre, int lows, ll val) {
	if ( i == lev * 2 - 1 ) {
		des->get(HashKey(lows, rem[0], rem[1], rem[2], rem[3])) += val;
		return;
	}
	if ( i & 1 ) {
		for ( int t1 = 0; t1 <= 1; t1 ++ )
			for ( int t2 = 0; t2 <= 1; t2 ++ ) {
				int sum = t1 + t2 + pre;
				if ( rem[sum] ) {
					rem[sum] --;
					expand(i + 1, lev, ups, t1, t2 ? setbit(lows, i / 2): lows, val);
					rem[sum] ++;
				}
			}
	} else {
		for ( int t0 = 0; t0 <= 1; t0 ++ ) 
			if ( lev == n || t0 == getbit(ups, i / 2) )
				for ( int t1 = 0; t1 <= 1; t1 ++ )
					if ( i == 0 || t1 == pre )
						for ( int t2 = 0; t2 <= 1; t2 ++ ) {
							int sum = t0 + t1 + t2;
							if ( rem[sum] ) {
								rem[sum] --;
								expand(i + 1, lev, ups, t2, lows, val);
								rem[sum] ++;
							}
						}
	}
}

int main() {
	scanf("%d", &n);
	for ( int i = 0; i < 4; i ++ )
		scanf("%d", &tot[i]);
	src = HM + 0, des = HM + 1;
	src->clear();
	src->get(HashKey(0, tot[0], tot[1], tot[2], tot[3])) = 1;
	for ( int lev = n; lev >= 1; lev -- ) {
		des->clear();
		for ( int k = 0; k < src->size; k ++ ) {
			memcpy(rem, src->ele[k].first.cnt, sizeof(rem));
			expand(0, lev, src->ele[k].first.s, 0, 0, src->ele[k].second);
		}
		swap(src, des);
	}
	ll ans = 0;
	for ( int k = 0; k < src->size; k ++ ) 
		ans += src->ele[k].second;
	printf(LL_FMT "\n", ans);
}
