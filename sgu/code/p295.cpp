#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef unsigned long long val_t;
const int LEN_MAX = 1010;
const int RUS[18] = {'A', 'B', 'C', 'E', 'H', 'K', 'M', 'O', 'P', 'T', 'X', 'a', 'c', 'e', 'o', 'p', 'x', 'y'};
int L, R, n;
val_t f[LEN_MAX][64];
bool del[LEN_MAX];
char str[LEN_MAX];
bool isRus[256];
int main() {
	freopen("t.in", "r", stdin);
	for ( int i = 0; i < 18; i ++ )
	   isRus[RUS[i]] = true;	
	scanf("%d%d\n", &L, &R);
	gets(str);
	int n = strlen(str);
	for ( int i = 0; i < n && str[i] == ' '; i ++ ) 
		del[i] = true;
	for ( int i = n - 1; i >= 0 && str[i] == ' '; i -- )
		del[i] = true;
	for ( int i = 0; i < n; i ++ ) 
		if ( !del[i] && str[i] == ' ' ) {
			int st = i;
			while ( i + 1 < n && !del[i + 1] && str[i + 1] == ' ' )
				i ++;
			int en = i;
			for ( int k = st + 1; k <= en; k ++ )
				del[k] = true;
		}
	int n2 = 0;
	for ( int i = 0; i < n; i ++ ) 
		if ( !del[i] )
			str[n2 ++] = str[i];
	n = n2;
	for ( int i = 0; i <= R; i ++ )
		f[0][i] = 1;
	for ( int i = 0; i < n; i ++ ) 
		for ( int j = 0; j <= R; j ++ )
			if ( f[i][j] > 0 ) {
				if ( isRus[(int)str[i]] && j < R ) 
					f[i + 1][j + 1] += 2 * f[i][j];
				else if ( str[i] == ' ' ) {
					for ( int k = 1; k <= R - j; k ++ )
						f[i + 1][j + k] += f[i][j];
				} else if ( j < R )
					f[i + 1][j + 1] += f[i][j];
			}
	val_t ans = 0;
	for ( int k = 0; k <= R; k ++ ) {
		int lb = max(0, L - k),
			rb = R - k;
		if ( lb <= rb )
			ans += f[n][k] * (rb - lb + 1);
	}
	cout << ans - 1;
}
