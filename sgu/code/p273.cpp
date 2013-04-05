#include <cstdio>
#include <cstring>
const char COLOR[4] = {'b', 'r', 'y', 'w'};
int conv[256];
int dpMemo[222][222];
bool dpDone[222][222];
char str[222];
int e[4][4];
int dp(int l, int r) {
	if ( l == r )
		return 1 << conv[str[l]];
	if ( dpDone[l][r] )
		return dpMemo[l][r];
	dpDone[l][r] = true;
	int &ret = dpMemo[l][r] = 0;
	for ( int k = l; k < r; k ++ ) {
		int s1 = dp(l, k), s2 = dp(k + 1, r);
		for ( int x = 0; x < 4; x ++ )
			if ( s1 & (1 << x) )
				for ( int y = 0; y < 4; y ++ )
					if ( s2 & (1 << y) ) 
						ret |= e[x][y];
	}
	return ret;
}
int main() {
	freopen("t.in", "r", stdin);
	conv['b'] = 0, conv['r'] = 1;
	conv['y'] = 2, conv['w'] = 3;
	int n[4];
	for ( int i = 0; i < 4; i ++ )
		scanf("%d", &n[i]);
	for ( int i = 0; i < 4; i ++ ) {
		for ( int t = 0; t < n[i]; t ++ ) {
			static char pat[4];
			scanf("%s", pat);
			e[conv[pat[0]]][conv[pat[1]]] |= 1 << i;
		}
	}
	scanf("%s", str);
	int len = strlen(str);
	int s = dp(0, len - 1);
	if ( s == 0 )
		puts("Nobody");
	else {
		for ( int i = 0; i < 4; i ++ )
			if ( s & (1 << i) )
				printf("%c", COLOR[i]);
		printf("\n");
	}
}
