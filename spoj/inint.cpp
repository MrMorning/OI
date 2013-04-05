#include <cstdio>
#include <cstring>
#include <cassert>

typedef long long ll;

const int TABLE[10] = {-1, 0, 1, -1, 2, -1, -1, -1, 3, -1};
const int DEP_MAX = 11;
const int DIG_MAX = 10;
const int inf = 0x3f3f3f3f;
const int MOD = 1000000007;

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
		} else if ( t.val == val ) {
			ways = ways + t.ways;
			if ( ways >= MOD )
				ways -= MOD;
		}
	}
};

Info combine(const Info &A, const Info &B) {
	return Info(A.val + B.val, (int)((ll)A.ways * B.ways % MOD));
}

struct Matrix {
	Info ele[DIG_MAX][DIG_MAX];
} memo[DEP_MAX][1 << DIG_MAX];
bool done[DEP_MAX][1 << DIG_MAX];
int log2[1 << DIG_MAX];

Matrix merge(const Matrix &A, const Matrix &B, int s, bool can_nine) {
	Matrix res;
	if ( can_nine )
		s |= 1 << 9;
	for ( int i = 0; i <= 9; i ++ )
		for ( int j = 0; j <= 9; j ++ ) {
			Info I1 = A.ele[i][j];
			if ( I1.val == inf )
				continue;
			I1.val ++;
			int tmp = s | 1 << j;
			while ( tmp ) {
				int v = tmp & -tmp;
				tmp -= v;
				int x = log2[v];
				int t = x + j;
				if ( t >= 10 ) {
					t -= 10;
					for ( int k = 0; k <= 9; k ++ ) {
						Info I2 = B.ele[t][k];
						if ( I1.val + I2.val > res.ele[i][k].val )
							continue;
						res.ele[i][k].update(combine(I1, I2));
					}
				}
			}
		}
	return res;
}

Matrix dp(int h, int s) {
	s &= ~1;
	if ( done[h][s] )
		return memo[h][s];
	done[h][s] = true;

	Matrix &res = memo[h][s];
	if ( h == 1 ) {
		for ( int x = 0; x <= 9; x ++ ) {
			res.ele[x][x].val = 0, res.ele[x][x].ways = 1;
			for ( int y = x; y <= 9; y ++ ) {
				for ( int t = 1; t <= 9; t ++ )
					if ( (s & (1 << t)) || t == y )
						if ( y + t <= 9 ) {
							Info tmp = res.ele[x][y];
							tmp.val ++;
							res.ele[x][y + t].update(tmp);
						}
			}
		}
	} else {
		res = dp(h - 1, s);
		for ( int x = 1; x <= 9; x ++ )
			res = merge(res, dp(h - 1, s | (1 << x)), s | (1 << (x - 1)), h > 2);
	}
	return res;
}

int get_mask(int x) {
	int res = 0;
	while ( x )
		res |= 1 << (x % 10), x /= 10;
	return res;
}

void solve(int lim) {

	if ( lim < 10 ) {
		if ( TABLE[lim] == -1 )
			printf("IMPOSSIBLE\n");
		else
			printf("%d 1\n", TABLE[lim]);
		return;
	}

	static int dig[12];
	int n_dig = 0;
	{
		int tmp = lim;
		while ( tmp ) {
			dig[++ n_dig] = tmp % 10, tmp /= 10;
		}
	}
	Matrix res;
	bool first = true;
	int cur_s = 0, pre_s = 0;
	bool pre_nine = false;
	for ( int i = n_dig; i >= 2; i -- ) {
		if ( i != n_dig )
			cur_s |= 1 << dig[i + 1];
		if ( first ) {
			res = dp(i - 1, cur_s);
			pre_nine = i > 2;
			first = false;
		} else if ( dig[i] != 0 ) {
			res = merge(res, dp(i - 1, cur_s), pre_s, pre_nine);
			pre_nine = i > 2;
			pre_s = cur_s;
		}
		for ( int j = 1; j < dig[i]; j ++ ) {
			res = merge(res, dp(i - 1, cur_s | (1 << j)), pre_s, pre_nine);
			pre_nine = i > 2;
			pre_s = cur_s | (1 << j);
		}
	}

	int delta;
	for ( int i = 2; i <= n_dig; i ++ ) {
		if ( dig[i] != 0 ) {
			int tmp = 0;
			for ( int j = n_dig; j > i; j -- )
				tmp = tmp * 10 + dig[j];
			tmp = tmp * 10 + dig[i] - 1;
			for ( int j = i - 1; j >= 2; j -- )
				tmp = tmp * 10 + 9;
			tmp *= 10;
			delta = tmp;
			break;
		}
	}
	Info f[10];
	for ( int i = 0; i <= 9; i ++ ) {
		Info I = res.ele[1][i];
		I.val ++;
		int real = delta + i;
		int s = get_mask(real);
		for ( int x = 1; x <= 9; x ++ )
			if ( s & (1 << x) ) 
				if ( x + i >= 10 ) {
					f[x + i - 10].update(I);
				}
	}

	for ( int i = 0; delta + 10 + i <= lim; i ++ ) {
		int real = delta + 10 + i;
		int s = get_mask(real);
		Info I = f[i];
		I.val ++;
		for ( int x = 1; x <= 9; x ++ )
			if ( s & (1 << x) ) 
				if ( x + i <= 9 ) {
					f[x + i].update(I);
				}
	}
	int des = lim - delta - 10;
	if ( f[des].val == inf )
		printf("IMPOSSIBLE\n");
	else
		printf("%d %d\n", f[des].val, f[des].ways);
}

int main() {
	freopen("t.in", "r", stdin);
	for ( int i = 0; i < DIG_MAX; i ++ )
		log2[1 << i] = i;
	int n;
	while ( scanf("%d", &n) != EOF ) 
		solve(n);
}
