#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long double val_t;

val_t bino[1111][1111], f[1111][1111];
int c[1111][1111], k[1111], p[1111];
pair<int, int> arr[1111];
bool fluct[1111];
int n, m, nArr;

inline int eval(pair<int, int> p) {
	return c[p.first][p.second];
}

bool cmpC(pair<int, int> p1, pair<int, int> p2) {
	return eval(p1) > eval(p2);
}

int main() {
	freopen("t.in", "r", stdin);
	bino[0][0] = 1;
	for ( int i = 1; i <= 1000; i ++ ) {
		bino[i][0] = 1;
		for ( int j = 1; j <= i; j ++ )
			bino[i][j] = bino[i-1][j-1]+bino[i-1][j];
	}
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= m; i ++ ) {
		scanf("%d", &k[i]);
		for ( int j = 1; j <= k[i]; j ++ ) {
			scanf("%d", &c[i][j]);
			arr[nArr++] = make_pair(i, j);
		}
	}
	sort(arr, arr+nArr, cmpC);
	int spe = eval(arr[n-1]), rem = n;
	for ( int i = 0; eval(arr[i]) != spe; i ++ ) {
		p[arr[i].first]++;
		rem--;
	}
	int left = 0;
	for ( int i = 0; i < nArr; i ++ )
		if ( eval(arr[i]) == spe ) {
			left++;
			fluct[arr[i].first] = true;
		}
	f[0][0] = 1.0;
	for ( int i = 1; i <= m; i ++ ) 
		for ( int j = 0; j <= i; j ++ ) {
			f[i][j] = f[i-1][j]*1.0/bino[k[i]][p[i]];
			if ( fluct[i] && j > 0) {
				f[i][j] += f[i-1][j-1]*1.0/bino[k[i]][p[i]+1];
			}
		}
	val_t ans = f[m][rem]/bino[left][rem];
	cout << setprecision(15) << setiosflags(ios::fixed) << ans;
}
