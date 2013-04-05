#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int kInf = 0x3f3f3f3f;
char A[4010], B[4010];
int ti, td, tr, te;
int f[4010][4010];
int nextA[4010][26], nextB[4010][26];
inline void upd(int &a, int b) {
	if ( b < a ) a = b;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &ti, &td, &tr, &te);
	scanf("%s%s", A, B);
	int nA = strlen(A), nB = strlen(B);
	memset(nextA, -1, sizeof(nextA));
	memset(nextB, -1, sizeof(nextB));
	for ( int i = nA-1; i >= 0; i -- ) {
		for ( int a = 0; a < 26; a ++ )
			nextA[i][a] = nextA[i+1][a];
		nextA[i][A[i]-'a'] = i;
	}
	for ( int i = nB-1; i >= 0; i -- ) {
		for ( int a = 0; a < 26; a ++ )
			nextB[i][a] = nextB[i+1][a];
		nextB[i][B[i]-'a'] = i;
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for ( int i = 0; i <= nA; i ++ )
		for ( int j = 0; j <= nB; j ++ ) 
			if ( f[i][j] != kInf ) {
				if ( j<nB )
					upd(f[i][j+1], f[i][j]+ti);
				if ( i<nA )
					upd(f[i+1][j], f[i][j]+td);
				if ( i<nA && j<nB ) {
					if ( A[i]==B[j] ) upd(f[i+1][j+1], f[i][j]);
					upd(f[i+1][j+1], f[i][j]+tr);
					if ( i+1<nA && j+1<nB ) {
						if ( nextA[i+1][B[j]-'a'] != -1 && nextB[j+1][A[i]-'a'] != -1 ) {
							int pa = nextA[i+1][B[j]-'a'], pb = nextB[j+1][A[i]-'a'];
							upd(f[pa+1][pb+1], f[i][j]+td*(pa-i-1)+te+ti*(pb-j-1));
						}
					}

				}
			}
	printf("%d\n", f[nA][nB]);
}
