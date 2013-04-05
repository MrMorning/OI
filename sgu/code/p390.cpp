#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif


struct Info {
	ll cnt; 
	int rem;
	Info(){}
	Info(ll cc, int rr):
		cnt(cc), rem(rr){}
} memo[20][165][1010];

struct Number {
	int dig[22];
	int nDig;
	ll val;
	void decompose() {
		memset(dig, 0, sizeof(dig));
		ll tmp = val;
		nDig = 0;
		while ( tmp ) {
			dig[nDig++] = tmp % 10;
			tmp /= 10;
		}
	}
} low, high;

bool done[20][165][1010];
int lim;


Info dp(int n, int s, int e) {
	if ( done[n][s][e] ) 
		return memo[n][s][e];
	done[n][s][e] = true;
	Info &ret = memo[n][s][e];
	if ( n == 0 ) {
		if ( s + e >= lim) return ret = Info(1, 0);
		else return ret = Info(0, e+s);
	}

	ret = Info(0, e);
	for ( int x = 0; x <= 9; x ++ ) {
		Info tmp = dp(n-1, s+x, ret.rem);
		ret.cnt += tmp.cnt, ret.rem = tmp.rem;
	}
	return ret;
}

int main() {
	freopen("t.in", "r", stdin);

	scanf(LL_FMT LL_FMT "%d", &low.val, &high.val, &lim);
	low.val--, high.val++;
	low.decompose();
	high.decompose();

	int n = high.nDig, m, pre = 0;
	for ( m = n-1; m >= 0; m -- ) 
		if ( low.dig[m] != high.dig[m] ) 
			break;	
		else
			pre += low.dig[m];

	Info ans(0, 0);
	for ( int i = 0; i < m; i ++ ) {
		int curPre = pre;
		for ( int j = m; j > i; j -- )
			curPre += low.dig[j];
		for ( int x = low.dig[i]+1; x <= 9; x ++ ) {
			Info tmp = dp(i, curPre+x, ans.rem);
			ans.cnt += tmp.cnt, ans.rem = tmp.rem;
		}
	}

	for ( int x = low.dig[m]+1; x < high.dig[m]; x ++ ) {
		Info tmp = dp(m, pre+x, ans.rem);
		ans.cnt += tmp.cnt, ans.rem = tmp.rem;
	}

	for ( int i = m-1; i >= 0; i -- ) {
		int curPre = pre;
		for ( int j = m; j > i; j -- )
			curPre += high.dig[j];
		for ( int x = 0; x < high.dig[i]; x ++ ) {
			Info tmp = dp(i, curPre+x, ans.rem);
			ans.cnt += tmp.cnt, ans.rem = tmp.rem;
		}
	}
	printf(LL_FMT "\n", ans.cnt);
}
