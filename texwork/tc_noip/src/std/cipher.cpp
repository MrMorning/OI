#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)

using namespace std;
typedef long long ll;
const int MOD = 1000000007;

vector<string> noSol() {
	return vector<string>(1, "NO SOLUTIONS");
}

class NumberGrid {
	public:
		int a[55][55], b[55][55];
		int sc[55], sr[55];
		int f[55][55 * 9], g[55][55 * 9];
		int n, m;
		vector<string> output() {
			bool okay = true;
			for ( int i = 0; i < n; i ++ )
				for ( int j = 0; j < m; j ++ ) {
					int sum = 0;
					for ( int x = 0; x < m; x ++ )
						sum += a[i][x];
					for ( int x = 0; x < n; x ++ )
						sum += a[x][j];
					sum -= a[i][j];
					okay &= sum == b[i][j];
				}
			if ( !okay ) 
				return noSol();
			vector<string> res(n, string(m, '?'));
			for ( int i = 0; i < n; i ++ )
				for ( int j = 0; j < m; j ++ ) {
					if ( a[i][j] < 0 || a[i][j] > 9 ) 
						return noSol();
					res[i][j] = (char)('0' + a[i][j]);
				}
			return res;
		}
		vector <string> decrypt() {
			int tot = 0;
			for ( int i = 0; i < n; i ++ )
				for ( int j = 0; j < m; j ++ )
					tot += b[i][j];
			if ( tot % (n + m - 1) != 0 ) return noSol();
			tot /= (n + m - 1);

			if ( tot == 0 || tot == 9 * n * m ) {
				for ( int i = 0; i < n; i ++ )
					for ( int j = 0; j < m; j ++ )
						a[i][j] = tot == 0 ? 0 : 9;

				return output();
			} 

			if ( n == 1 && m == 1 ) {
				a[0][0] = b[0][0];
				return output();
			} else if ( n == 1 || m == 1 ) {
				if ( m == 1 ) {
					m = n;
					for ( int i = 0; i < n; i ++ )
						b[0][i] = b[i][0];
				}

				for ( int i = 0; i < m; i ++ )
					if ( b[0][i] != b[0][0] ) return noSol();

				f[0][0] = 1;
				g[0][0] = 1;
				for ( int i = 0; i < m; i ++ )
					for ( int j = tot; j >= 0; j -- )
						for ( int k = 0; k <= 9; k ++ )
							if ( j >= k ) {
								f[i+1][j] = (f[i+1][j] + f[i][j - k]) % MOD;
								g[i+1][j] |= g[i][j-k];
							}
				if ( !g[m][tot] ) return noSol();
				stringstream ss;
				ss << f[m][tot] << " SOLUTIONS";
				return vector<string>(1, ss.str());
			}
			for ( int i = 0; i < n; i ++ ) {
				sr[i] = 0;
				for ( int j = 0; j < m; j ++ )
					sr[i] += b[i][j];
				sr[i] -= tot;
				if ( sr[i] % (m - 1) != 0 )
					return noSol();
				sr[i] /= m - 1;
			}
			for ( int j = 0; j < m; j ++ ) {
				sc[j] = 0;
				for ( int i = 0; i < n; i ++ )
					sc[j] += b[i][j];
				sc[j] -= tot;
				if ( sc[j] % (n - 1) != 0 ) 
					return noSol();
				sc[j] /= n - 1;
			}
			for ( int i = 0; i < n; i ++ )
				for ( int j = 0; j < m; j ++ ) 
					a[i][j] = sr[i] + sc[j] - b[i][j];
			return output();
		}
} cls;

int main() {
	freopen("cipher.in", "r", stdin);
	freopen("cipher.out", "w", stdout);
	int nRow, nCol;
	scanf("%d%d", &nRow, &nCol);
	cls.n = nRow, cls.m = nCol;
	for ( int i = 0; i < nRow; i ++ )
		for ( int j = 0; j < nCol; j ++ )
			scanf("%d", &cls.b[i][j]);
	vector<string> ans = cls.decrypt();
	if ( ans[0].find("SOLUTION") == string::npos )
		for ( int i = 0; i < nRow; i ++, puts("") )
			for ( int j = 0; j < nCol; j ++ )
				printf("%c ", ans[i][j]);
	else
		printf("%s\n", ans[0].c_str());
}
