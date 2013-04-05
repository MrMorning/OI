#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
const int inf = 0x3f3f3f3f;
int N, M, K;
bool dpDone[1 << 15];
int dpMemo[1 << 15], dpRoute[1 << 15];
bitset<10000> blk[6], ctr[15];
int nCtr;
int out[10000];
int countBits(int s) {
	int ret = 0;
	while ( s ) {
		s >>= 1;
		ret ++;
	}
	return ret;
}
int dp(int s) {
	if ( s == 0 )
		return 0;
	if ( dpDone[s] )
		return dpMemo[s];
	dpDone[s] = true;
	int &val = dpMemo[s] = inf;
	int t;
	{
		int tmp = s & -s;
		t = -1;
		while ( tmp )
			t ++, tmp >>= 1;
	}
	for ( int i = 0; i < N * M; i ++ )
		if ( ctr[t][i] ) {
			int ns = s;
			for ( int k = 0; k < nCtr; k ++ )
				if ( s & (1 << k) ) {
					if ( ctr[k][i] ) 
						ns -= 1 << k;
				}
			int tmp = dp(ns) + 1;
			if ( tmp < val ) {
				val = tmp;
				dpRoute[s] = i;
			}
		}
	return val;
}

void genSol(int s) {
	if ( s == 0 )
		return;
	int t;
	{
		int tmp = s & -s;
		t = -1;
		while ( tmp )
			t ++, tmp >>= 1;
	}
	out[dpRoute[s]] = 1;
	int ns = s;
	for ( int k = 0; k < nCtr; k ++ )
		if ( s & (1 << k) ) {
			if ( ctr[k][dpRoute[s]] ) 
				ns -= 1 << k;
		}
	genSol(ns);
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for ( int k = 0; k < K; k ++ ) {
		for ( int i = 0; i < N; i ++ ) {
			char str[15];
			scanf("%s", str);
			for ( int j = 0; j < M; j ++ )
				if ( str[j] == '1' )
					blk[k].set(i * M + j);
		}
	}
	for ( int a = 0; a < K; a ++ )
		for ( int b = a + 1; b < K; b ++ ) 
			ctr[nCtr ++] = blk[a] ^ blk[b];
	printf("%d\n", dp((1 << nCtr) - 1));
	genSol((1 << nCtr) - 1);
	for ( int i = 0; i < N; i ++ , puts(""))
		for ( int j = 0; j < M; j ++ )
			printf("%d", out[i * M + j]);
}
