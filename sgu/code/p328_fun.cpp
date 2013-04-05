#include <cstdio>
#include <bitset>
using namespace std;
const int kLenMax = 1000;
bool dpDone[kLenMax][3][3];
int dpMemo[kLenMax][3][3];

int dp(int n, int s1, int s2) {
	if ( dpDone[n][s1][s2] )
		return dpMemo[n][s1][s2];
	dpDone[n][s1][s2] = true;
	int &res = dpMemo[n][s1][s2];
	if ( n == 0 )
		return res = 0;
	if ( n == 1 ) {
		if ( s1 + s2 == 3 )
			return res = 0;
		return res = 1;
	}
	bitset<kLenMax> bset;
	for ( int k = 0; k < n; k ++ ) {
		if ( !((k == 0 && s1 == 1) || (k == n - 1 && s2 == 1)))
			bset.set(dp(k, s1, 1) ^ dp(n - k - 1, 1, s2));
		if ( !((k == 0 && s1 == 2) || (k == n - 1 && s2 == 2)))
			bset.set(dp(k, s1, 2) ^ dp(n - k - 1, 2, s2));
	}
	for ( res = 0; bset[res]; res ++ );
	return res;
}

int main() {
	for ( int n = 1; n <= 100; n ++ )
		printf("n=%d,f=%d\n", n, dp(n, 1, 1));
}
