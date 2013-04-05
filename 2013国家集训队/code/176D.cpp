#include <cstdio>
#include <cstring>
#include <algorithm>
#define mp(a, b) make_pair(a, b)
using namespace std;
const int kNMax = 2005;
const int kLenMax = 1000005;

int n, m;
int st[kNMax], en[kNMax], len[kNMax];
int nxt[kLenMax][26];
pair<int, int> f[kNMax][kNMax], g[kNMax][26];
bool ex[kNMax][kNMax];
char str[kLenMax], ptr[kNMax];
int id[kNMax];

inline void upd(int i, int j, pair<int, int> val) {
	if ( !ex[i][j] ) {
		ex[i][j] = true;
		f[i][j] = val;
	} else
		f[i][j] = min(f[i][j], val);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int tot = 0;
	for ( int i = 0; i < n; i ++ ) {
		st[i] = tot;
		scanf("%s", str+tot);
		len[i] = strlen(str+tot);
		en[i] = st[i]+len[i]-1;
		tot += len[i];
	}
	memset(nxt, -1, sizeof(nxt));
	for ( int i = 0; i < n; i ++ ) {
		nxt[en[i]][str[en[i]]-'a'] = en[i];
		for ( int j = en[i]-1; j >= st[i]; j-- ) {
			nxt[j][str[j]-'a'] = j;
			for ( int z = 0; z < 26; z ++ )
				if ( z != str[j]-'a' )
					nxt[j][z] = nxt[j+1][z];
		}
	}
	scanf("%d", &m);
	for ( int i = 0; i < m; i ++ ) {
		scanf("%d", &id[i]);
		--id[i];
	}
	for ( int z = 0; z < 26; z ++ ) g[m][z].second = -1;
	for ( int i = m-1; i >= 0; i -- ) {
		for ( int z = 0; z < 26; z ++ ) {
			if ( nxt[st[id[i]]][z] != -1 )
				g[i][z] = mp(i, nxt[st[id[i]]][z]);
			else
				g[i][z] = g[i+1][z];
		}
	}
	scanf("%s", ptr);
	int plen = strlen(ptr);
	f[0][0] = mp(0, st[id[0]]);
	ex[0][0] = true;
	for ( int i = 0; i < plen; i ++ )
		for ( int j = 0; j < plen; j ++ )
			if ( ex[i][j] ) {
				pair<int, int> pos = f[i][j];
				upd(i+1, j, pos);
				if ( pos.first == m ) continue;
				int real = pos.second;
				pair<int, int> des = make_pair(pos.first, nxt[real][ptr[i]-'a']);
				if ( des.second == -1 )
					des = g[pos.first+1][ptr[i]-'a'];
				if ( des.second != -1 ) {
					if ( des.second+1 <= en[id[des.first]] )
						des.second++;
					else
						des.first++, des.second = st[id[des.first]];
					upd(i+1, j+1, des);
				}
			}
	int ans = -1;
	for ( int j = 0; j <= plen; j ++ )
		if ( ex[plen][j] ) ans = j;
	printf("%d\n", ans);
}
