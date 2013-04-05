#include <cstdio>
#include <cstring>
#include <cassert>

typedef long long ll;

const int inf = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N_MAX = 200000;

struct Info {
	int val, ways;
	Info() {
		val = inf;
		ways = 0;
	}
	Info(int _val, int _ways):
		val(_val), ways(_ways){}
	void update(const Info &t) {
		if ( t.val < val ) {
			val = t.val;
			ways = t.ways;
		} else if ( t.val == val )
			ways = (ways + t.ways) % MOD;
	}
} f[N_MAX];

int get_mask(int x) {
	int res = 0;
	while ( x )
		res |= 1 << (x % 10), x /= 10;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	f[1] = Info(0, 1);
	for ( int i = 1; i <= N_MAX; i ++ ) {
		int s = get_mask(i);
		Info I = f[i];
		I.val ++;
		for ( int x = 1; x <= 9; x ++ )
			if ( s & (1 << x ) ) 
				f[i + x].update(I);
	}
	int n;
	while ( scanf("%d", &n) != EOF ) {
		if ( f[n].val == inf ) 
			printf("IMPOSSIBLE\n");
		else
			printf("%d %d\n", f[n].val, f[n].ways);
	}
}
