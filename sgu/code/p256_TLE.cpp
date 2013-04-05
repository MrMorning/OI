#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 99991;
const int inf = 0x3f3f3f3f;
const int STATE_MAX = 1000000;
int POW5[11];
int A[10], B[10];
int nBall, nVol;
struct State {
	int n, s[10];
	int com;
	State(){}
	State(int _n, int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9) {
		n = _n;
		s[0] = s0, s[1] = s1, s[2] = s2, s[3] = s3, s[4] = s4;
		s[5] = s5, s[6] = s6, s[7] = s7, s[8] = s8, s[9] = s9;
		com = 0;
		for ( int k = 0; k < nVol; k ++ )
			com = com + POW5[k] * s[k];
		com = com + POW5[nVol] * n;
	}
	int hash() const {
		return com % MOD;
	}
	bool operator== (const State &t) const {
		return com == t.com;
	}
	bool canRest() {
		bool res = false;
		for ( int k = 0; !res && k < nVol; k ++ )
			res |= s[k] > 0;
		return res;
	}
	State rest() {
		State tmp = *this;
		for ( int k = 0; k < nVol; k ++ )
			if ( tmp.s[k] ) {
				tmp.s[k] --;
				tmp.com -= POW5[k];
			}
		return tmp;
	}
	State move(int t) {
		State tmp = rest();
		tmp.com -= tmp.n * POW5[nVol];
		tmp.n = max(0, tmp.n - A[t]);
		tmp.com += tmp.n * POW5[nVol];
		tmp.com -= tmp.s[t] * POW5[t];
		tmp.com += B[t] * POW5[t];
		tmp.s[t] = B[t];
		return tmp;
	}
};

struct HashTable {
	pair<State, int> ele[STATE_MAX];
	int next[STATE_MAX], begin[MOD];
	int size;
	void clear() {
		size = 0;
		memset(begin, -1, sizeof(begin));
	}
	int &get(const State &s) {
		int code = s.hash();
		for ( int e = begin[code]; e != -1; e = next[e] ) 
			if ( ele[e].first == s )
				return ele[e].second;
		ele[size] = make_pair(s, -1);
		next[size] = begin[code];
		begin[code] = size;
		return ele[size++].second;
	}
} memo;

int dp(State s) {
	int &val = memo.get(s);
	if ( val != -1 )
		return val;
	if ( s.n == 0 )
		return val = 0;
	if ( s.canRest() )
		val = dp(s.rest()) + 1;
	else
		val = inf;
	for ( int k = 0; k < nVol; k ++ )
		if ( s.s[k] == 0 ) 
			val = min(val, dp(s.move(k)) + 1);
	return val;
}

int main() {
	freopen("t.in", "r", stdin);
	memo.clear();
	POW5[0] = 1;
	for ( int i = 1; i <= 10; i ++ )
		POW5[i] = POW5[i - 1] * 5;
	scanf("%d%d", &nBall, &nVol);
	for ( int i = 0; i < nVol; i ++ )
		scanf("%d%d", &A[i], &B[i]);
	int ans = dp(State(nBall, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
	printf("%d\n", ans);
}
