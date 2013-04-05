#include <cstdio>
#include <cstring>

const int DEP_MAX = 30;
const int DIG_MAX = 10;
const int inf = 0x3f3f3f3f;


struct Info {
	int val, ways;
	Info() {
		val = inf;
		ways = 0;
	}
	Info(int _val, int _ways):
		val(_val), ways(_ways){}
} memo[DEP_MAX][1 << DIG_MAX][DIG_MAX][DIG_MAX];
bool done[DEP_MAX][1 << DIG_MAX][DIG_MAX];

Info better(const Info &a, const Info &b) {
	Info res = a;
	if ( b.val < res.val ) 
		res = b;
	else if ( b.val == res.val )
		res.ways += b.ways;
	return res;
}

Info combine(const Info &a, const Info &b) {
	Info res = a;
	res.val += b.val;
	res.ways *= b.ways;
	return res;
}

Info dp(int h, int s, int be, int en) {
	if ( done[h][s][be] )
		return memo[h][s][be][en];
	done[h][s][be] = true;

	if ( h == 1 ) {
		static Info f[10];
		f[be] = Info(0, 1);
		for ( int i = be; i <= 8; i ++ ) {
			int ns = s | (1 << i);
			for ( int x = 1; x <= 9; x ++ )
				if ( ns & (1 << x) && i + x < 10 )
					f[i + x] = better(f[i + x], f[i]);	
		}
		memcpy(memo[h][s][be], f, sizeof(f));
	} else {
		Info st_res[10], en_res[10];

		st_res[be].val = 0, st_res[be].ways = 1;
		for ( int pos = 0; pos <= 9; pos ++ ) {
			if ( pos > 0 ) {
				for ( int x = 0; x <= 8; x ++ )
					st_res[x] = Info();

				for ( int x = 1; x <= 9; x ++ ) {
					int ns = s | (1 << (pos - 1));
					ns |= 1 << 9;
					for ( int y = 1; y <= 9; y ++ )
						if ( ns & (1 << y) ) {
							if ( x + y >= 10 ) 
								st_res[x + y - 10] = better(st_res[x + y - 10], Info(en_res[x].val + 1, en_res[x].ways));
						}
				}
			}

			for ( int x = 1; x <= 9; x ++ )
				en_res[x] = Info();

			for ( int st_num = 0; st_num <= 8; st_num ++ ) {
				for ( int en_num = 1; en_num <= 9; en_num ++ ) 
					en_res[en_num] = combine(st_res[st_num], dp(h - 1, s | (1 << pos), st_num, en_num));
			}
		}
		memcpy(memo[h][s][be], en_res, sizeof(en_res));
	}
	return memo[h][s][be][en];
}

int main() {
	freopen("t.in", "r", stdin);
}
