#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
typedef long long ll;
using namespace std;
const int kMod = 12345;

inline void add(int &a, int b) {
	a = (a + b) % kMod;
}

inline int mul(int a, int b) {
	return a * b % kMod;
}

struct Matrix {
	int ele[123][123];
	int n, m;
} T, F, IdMat;

Matrix operator* (const Matrix &A, const Matrix &B) {
	static Matrix res;
	assert(A.m == B.n);
	res.n = A.n, res.m = B.m;
	for ( int i = 0; i < res.n; i ++ ) 
		for ( int j = 0; j < res.m; j ++ ) {
			res.ele[i][j] = 0;
			for ( int k = 0; k < A.m; k ++ )
				add(res.ele[i][j], mul(A.ele[i][k], B.ele[k][j]));
	}
	return res;
}

Matrix powMat(Matrix A, ll n) {
	Matrix res = n & 1 ? A : IdMat;
	for ( n >>= 1; n; n >>= 1 ) {
		A = A * A;
		if ( n & 1 ) 
			res = res * A;
	}
	return res;
}


int cond[1000];
int nCond;

vector<int> cur, sta[123];
map<vector<int>, int> mp;
vector<int> pos[26];
bool exist[26], ignore[26];
int nSta;
bool final[123];

void generate(int i) {
	if ( i == nCond ) {
		sta[nSta++] = cur;
		mp[cur] = nSta-1;
		return;
	}
	for ( int x = 0; x < cond[i]; x ++ ) {
		cur.push_back(x);
		generate(i+1);
		cur.pop_back();
	}
}

int main() {
	freopen("t.in", "r", stdin);
	ll rep;
	int n;
	scanf(LL_FMT "%d", &rep, &n);
	for ( int i = 0; i < n; i ++ ) {
		static char ts[5];
		scanf("%s%d", ts, &cond[nCond]);
		exist[ts[0]-'A'] = true;
		if ( cond[nCond] == 1 ) {
			ignore[ts[0]-'A'] = true;
			continue;
		}
		nCond++;
		pos[ts[0]-'A'].push_back(nCond-1);
	}
	generate(0);
	T.n = T.m = nSta;
	IdMat.n = IdMat.m = nSta;
	for ( int i = 0; i < nSta; i ++ ) 
		IdMat.ele[i][i] = 1;
	for ( int i = 0; i < nSta; i ++ ) {
		for ( int ch = 0; ch < 26; ch ++ ) 
			if ( exist[ch] ) {
				vector<int> t = sta[i];
				foreach(it, pos[ch]) 
					t[*it] = (t[*it]+1) % cond[*it];
				int j = mp[t];
				T.ele[j][i]++;
			}

		final[i] = true;
		for ( int ch = 0; ch < 26; ch ++ ) 
			if ( exist[ch] && !ignore[ch] ) {
				bool found = false;
				foreach(it, pos[ch]) 
					if ( sta[i][*it] == 0 ) {
						found = true;
						break;
					}
				if ( !found ) {
					final[i] = false;
					break;
				}
			}
	}
	F.n = nSta, F.m = 1;
	F.ele[0][0] = 1;

	F = powMat(T, rep) * F;
	int ans = 0;
	for ( int i = 0; i < nSta; i ++ )
		if ( final[i] )
			add(ans, F.ele[i][0]);
	printf("%d\n", ans);
}
