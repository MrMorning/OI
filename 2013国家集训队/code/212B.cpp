#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;

const int kLenMax = 1000010;
const int kMod = 999991;
const int kSize = 10110;

char str[kLenMax];
int pre[2][26];
char C[10100][30];

struct HashMap {
	int begin[kMod], next[kSize], key[kSize], val[kSize];
	int size;
	void init() {
		size = 0;
		memset(begin, -1, sizeof(begin));
	}
	void insert(int msk) {
		int code = msk % kMod;
		for ( int e = begin[code]; e != -1; e = next[e] )
			if ( key[e] == msk ) return;
		next[size] = begin[code];
		key[size] = msk;
		val[size] = 0;
		begin[code] = size;
		size++;
	}
	void add(int msk) {
		int code = msk % kMod;
		for ( int e = begin[code]; e != -1; e = next[e] )
			if ( key[e] == msk ) {
				val[e]++;
				return;
			}
	}
	int find(int msk) {
		int code = msk % kMod;
		for ( int e = begin[code]; e != -1; e = next[e] )
			if ( key[e] == msk ) {
				return val[e];
			}
		assert(0);
	}
} HM;

int main() {
	freopen("t.in", "r", stdin);
	HM.init();
	int m;
	scanf("%s", str);
	scanf("%d", &m);
	for ( int i = 0; i < m; i ++ ) {
		scanf("%s", C[i]);
		int l = strlen(C[i]), msk = 0;
		for ( int j = 0; j < l; j ++ )
			msk |= 1 << (C[i][j]-'a');
		HM.insert(msk);
	}

	int len = strlen(str);
	str[len++] = '$';
	memset(pre, -1, sizeof(pre));
	for ( int i = 1; i < len; i ++ ) {
		static int tmp[26];
		int nTmp = 0;
		pre[i&1][str[i-1]-'a'] = i-1;
		for ( int z = 0; z < 26; z ++ )
			if ( z != str[i-1]-'a' )
				pre[i&1][z] = pre[(i-1)&1][z];
		for ( int z = 0; z < 26; z ++ )
			if ( pre[i&1][z] != -1 )
				tmp[nTmp++] = pre[i&1][z];
		sort(tmp, tmp+nTmp);
		int msk = 0;
		for ( int j = nTmp-1; str[tmp[j]] != str[i] && j >= 0; j -- ) {
			msk |= 1 << (str[tmp[j]]-'a');
			HM.add(msk);
		}
	}
	for ( int i = 0; i < m; i ++ ) {
		int l = strlen(C[i]), msk = 0;
		for ( int j = 0; j < l; j ++ )
			msk |= 1 << (C[i][j]-'a');
		printf("%d\n", HM.find(msk));
	}
}
