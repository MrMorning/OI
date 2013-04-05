#include <cstdio>
#include <cassert>
#include <cstring>
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

const ull BASE1 = 1000, BASE2 = 1000*BASE1, 
	  BASE3 = 1000*BASE2, BASE4 = 1000*BASE3, BASE5 = 1000*BASE4;
const int kMod = 1099991;
const int kSzMax = 3000000;

struct State {
	int n, a[4];
	bool is0;
	ull id;
	ull getID() {
		return (ull)(222+n)*BASE5+(ull)(222+a[0])*BASE4
			+(ull)(222+a[1])*BASE3+(ull)(222+a[2])*BASE2
			+(ull)(222+a[3])*BASE1+(ull)is0;
	}
	State(){}
	State(int _n, int a0, int a1, int a2, int a3) {
		n = _n;
		a[0] = a0, a[1] = a1, a[2] = a2, a[3] = a3;
		is0 = false;
		id = getID();
	}
	State(int _n) {
		n = _n;
		a[0] = a[1] = a[2] = a[3] = 0;
		is0 = true;
		id = getID();
	}

	State exp(int c0, int c1, int c2, int c3) {
		return State(n+1, a[0]+c0, a[1]+c1, a[2]+c2, a[3]+c3);
	}
};

struct HashMap {
	int begin[kMod], next[kSzMax], size;
	State key[kSzMax];
	uint val[kSzMax];
	void init() {
		size = 0;
		memset(begin, -1, sizeof(begin));
	}
	void add(State s, uint v) {
		int code = s.id % kMod;
		for ( int e = begin[code]; e != -1; e = next[e] ) 
			if ( key[e].id == s.id ) {
				val[e] += v;
				return;
			}
		next[size] = begin[code];
		begin[code] = size;
		key[size] = s;
		val[size] = v;
		size++;
	}
	uint find(State s) {
		int code = s.id % kMod;
		for ( int e = begin[code]; e != -1; e = next[e] ) 
			if ( key[e].id == s.id ) 
				return val[e];
		return 0;
	}
} HM;

void prework() {
	HM.init();
	HM.add(State(1),1);
	HM.add(State(1, 0, 0, 0, 0),1);
	HM.add(State(1, 1, 0, 0, 0),1);
	HM.add(State(1, 0, 1, 0, 0),1);
	HM.add(State(1, 2, 0, 0, 0),1);
	HM.add(State(1, 0, 0, 1, 0),1);
	HM.add(State(1, 1, 1, 0, 0),1);
	HM.add(State(1, 0, 0, 0, 1),1);
	HM.add(State(1, 3, 0, 0, 0),1);
	HM.add(State(1, 0, 2, 0, 0),1);

	for ( int i = 0; i < HM.size; i ++ ) {
		State cs = HM.key[i];
		if ( cs.is0 || cs.n == 18 ) continue;
		if ( cs.n % 2 == 0 ) {
			//mul
			HM.add(State(cs.n+1), HM.val[i]);
			HM.add(cs.exp(0, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(1, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, 1, 0, 0), HM.val[i]);
			HM.add(cs.exp(2, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, 0, 1, 0), HM.val[i]);
			HM.add(cs.exp(1, 1, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, 0, 0, 1), HM.val[i]);
			HM.add(cs.exp(3, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, 2, 0, 0), HM.val[i]);
		} else {
			//div
			HM.add(cs.exp(0, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(-1, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, -1, 0, 0), HM.val[i]);
			HM.add(cs.exp(-2, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, 0, -1, 0), HM.val[i]);
			HM.add(cs.exp(-1, -1, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, 0, 0, -1), HM.val[i]);
			HM.add(cs.exp(-3, 0, 0, 0), HM.val[i]);
			HM.add(cs.exp(0, -2, 0, 0), HM.val[i]);
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	prework();
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		int L;
		ll V;
		scanf("%d" LL_FMT, &L, &V);
		if ( V == 0 ) 
			printf("%u\n", HM.find(State(L)));
		else {
			int cnt[4];
			memset(cnt, 0, sizeof(cnt));
			while ( V % 2 == 0 )
				V /= 2, cnt[0]++;
			while ( V % 3 == 0 )
				V /= 3, cnt[1]++;
			while ( V % 5 == 0 )
				V /= 5, cnt[2]++;
			while ( V % 7 == 0 )
				V /= 7, cnt[3]++;
			if ( V != 1 ) printf("0\n");
			else {
				printf("%u\n", HM.find(State(L,cnt[0],cnt[1],cnt[2],cnt[3])));
			}
		}
	}
}
