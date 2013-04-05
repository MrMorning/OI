#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;
const int TST_MAX = 1000;
int perm[111], L[111], R[111];
int countBits(int n) {
	int res = 0;
	while ( n ) {
		res += n & 1;
		n >>= 1;
	}
	return res;
}
int main() {
	int n = 6;
	srand(42);
	for ( int tst = 0; tst < TST_MAX; tst ++ ) {
		for ( int i = 0; i < n; i ++ )
			L[i] = rand() % 10000, R[i] = rand() % 10000;
		for ( int i = 0; i < n; i ++ )
			perm[i] = i;
		int res = 0;
		do {
			int tmp = 0;
			for ( int i = 0; i < n; i ++ )
				tmp |= (countBits(L[i] & R[perm[i]])) % 2;
			res += tmp & 1;
		} while ( next_permutation(perm, perm + n) );
		fprintf(stderr, "%d\n", res);
		res %= 2;

		//check
		int res2 = 0;
		for ( int i = 0; i < n; i ++ )
			for ( int j = 0; j < n; j ++ )
				res2 |= countBits(L[i] ^ R[j]) & 1;

		//assert(res == res2);
	}
}
