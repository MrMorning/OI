#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;

const int kNMax = 55;
const int kInf = 0x3f3f3f3f;

bool done[26][kNMax][kNMax][2], memo[26][kNMax][kNMax][2];
char str[2][kNMax];
int len[2];
vector<pair<int, int> > list[26];
bool g[26][kNMax][kNMax];
int f[kNMax][kNMax];

bool canExpand(int ch, int l, int r, int t) {
	if ( done[ch][l][r][t] ) return memo[ch][l][r][t];
	done[ch][l][r][t] = true;
	bool &res = memo[ch][l][r][t] = false;
	if ( l == r ) 
		res = (str[t][l] == ch+'a');
	else {
		foreach(it, list[ch]) {
			for ( int k = l; k < r; k ++ )
				res |= canExpand(it->first-'a', l, k, t) && canExpand(it->second-'a', k+1, r, t);
		}
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s\n", str[0]);
	scanf("%s\n", str[1]);
	for ( int t = 0; t < 2; t ++ )
		len[t] = strlen(str[t]);
	int nSub;
	scanf("%d\n", &nSub);
	for ( int i = 0; i < nSub; i ++ ) {
		char c1, c2, c3;
		scanf("%c->%c%c\n", &c1, &c2, &c3);
		list[c1-'a'].push_back(make_pair(c2, c3));
	}

	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;

	for ( int i = 1; i <= len[0]; i ++ )
		for ( int j = 1; j <= len[1]; j ++ ) {
			for ( int ii = 1; ii <= i; ii ++ )
				for ( int jj = 1; jj <= j; jj ++ )
					for ( int ch = 0; ch < 26; ch ++ )
					if ( canExpand(ch, ii-1, i-1, 0) && canExpand(ch, jj-1, j-1, 1) )
						f[i][j] = min(f[i][j], f[ii-1][jj-1] + 1);
		}
	printf("%d\n", f[len[0]][len[1]] == kInf ? -1 : f[len[0]][len[1]]);
}
