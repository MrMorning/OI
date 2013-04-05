#include <cstdio>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int N, M, K;
bool dpDone[1 << 6];
int dpMemo[1 << 6];
pair<int, int> dpRoute[1 << 6];
char blk[6][12][12];
int out[12][12];
int countBits(int s) {
	int ret = 0;
	while ( s ) {
		ret += s & 1;
		s >>= 1;
	}
	return ret;
}
int dp(int s) {
	if ( dpDone[s] )
		return dpMemo[s];
	dpDone[s] = true;
	int &val = dpMemo[s] = inf;
	if ( countBits(s) <= 1 )
		return val = 0;
	for ( int x = 0; x < N; x ++ )
		for ( int y = 0; y < M; y ++ ) {
			int s1 = 0, s2 = 0;
			for ( int k = 0; k < K; k ++ ) 
				if ( s & (1 << k) ) {
					if ( blk[k][x][y] == '0' )
						s1 |= 1 << k;
					else
						s2 |= 1 << k;
				}
			if ( s1 != 0 && s2 != 0 ) {
				int tmp = dp(s1) + dp(s2) + 1;
				if ( tmp < val ) {
					val = tmp;
					dpRoute[s] = make_pair(x, y);
				}
			}
		}
	return val;
}

void genSol(int s) {
	if ( countBits(s) <= 1 )
	   return;	
	int x = dpRoute[s].first, 
		y = dpRoute[s].second;
	out[x][y] = 1;
	int s1 = 0, s2 = 0;
	for ( int k = 0; k < K; k ++ ) 
		if ( s & (1 << k) ) {
			if ( blk[k][x][y] == '0' )
				s1 |= 1 << k;
			else
				s2 |= 1 << k;
		}
	genSol(s1);
	genSol(s2);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &N, &M, &K);
	for ( int k = 0; k < K; k ++ ) {
		for ( int i = 0; i < N; i ++ )
			scanf("%s", blk[k][i]);
	}
	printf("%d\n", dp((1 << K) - 1));
	genSol((1 << K) - 1);
	for ( int i = 0; i < N; i ++ , puts(""))
		for ( int j = 0; j < M; j ++ )
			printf("%d", out[i][j]);
}
