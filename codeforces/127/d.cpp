#include <cstdio>
#include <map>
#include <cstring>
using namespace std;

typedef unsigned long long ull;
const int BASE = 99991;
const int inf = 0x3f3f3f3f;

ull getHash(char *s) {
	int n = strlen(s);
	ull ret = 0;
	for ( int i = 0; i < n; i ++ )
		ret = ret * BASE + s[i]; 
	return ret;
}

void upd(int &x, int y) {
	x = min(x, y);
}

map<ull, int> mp;
int n, m, nArr, arr[500010];
int list[15][500010], nList[15], near[15][500010];
int val[1<<15][15];
int f[1<<15][110];
pair<int, int> ans[111];
int nAns;

bool isBelong(int s1, int s2) {
	return (s1 & s2) == s2;
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		static char word[15];
		scanf("%s", word);
		mp[getHash(word)] = i;
	}
	scanf("%d", &m);
	for ( int tst = 1; tst <= m; tst ++ ) {
		int sz;
		scanf("%d", &sz);
		nArr = 0;
		for ( int i = 0; i < sz; i ++ ) {
			static char ts[15];
			scanf("%s", ts);
			ull code = getHash(ts);
			if ( mp.count(code) ) 
				arr[nArr++] = mp[code];
		}
		for ( int i = 0; i < n; i ++ )
			nList[i] = 0;
		memset(val, 0, sizeof(val));
		for ( int s = 0; s < (1 << n); s ++ ) 
			for ( int x = 0; x < n; x ++ )
				if ( !(s & (1 << x)) )
					for ( int y = 0; y < n; y ++ )
						if ( s & (1 << y) ) 
							if ( y > x )
								val[s][x]++;

		memset(near, 0x3f, sizeof(near));
		for ( int i = 0; i < nArr; i ++ ) {
			int x = arr[i];
			for ( int j = (nList[x] ? list[x][nList[x]-1] + 1 : 0); j <= i; j ++ )
				near[x][j] = i;
			list[x][nList[x]++] = i;
		}

		memset(f, 0x3f, sizeof(f));
		for ( int i = 0; i < nArr; i ++ )
			upd(f[1<<arr[i]][0], i);
		for ( int s = 1; s < (1 << n); s ++ ) 
			for ( int k = 0; k < n * (n-1) / 2; k ++ ) 
				if ( f[s][k] != inf ) {
					int p = f[s][k];
					for ( int x = 0; x < n; x ++ )
						if ( !(s & (1 << x)) ) {
							int q = near[x][p];
							upd(f[s + (1<<x)][k + val[s][x]], q);
						}
				}

		for ( int k = 0; k <= n * (n - 1) / 2; k ++ )
			if ( f[(1<<n) - 1][k] != inf ) {
				ans[nAns++] = make_pair(n * (n - 1) / 2 - k + 1, -tst);
				break;
			}
	}
	if ( nAns == 0 )
		printf("Brand new problem!\n");
	else {
		pair<int, int> best = make_pair(-1, 0);
		for ( int i = 0; i < nAns; i ++ ) 
			best = max(best, ans[i]);
		printf("%d\n", -best.second);
		printf("[:");
		while ( best.first -- )
			printf("|");
		printf(":]");
	}
}
