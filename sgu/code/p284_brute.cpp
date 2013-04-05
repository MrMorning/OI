#include <cstdio>
#include <cstring>
char comp[33][101000];
int compSz[33];
char pat[111];
int patLen;
char acc[101000];
int countMatch(const char *s, int n) {
	int res = 0;
	for ( int i = 0; i + patLen - 1 < n; i ++ )
		if ( strncmp(s + i, pat, patLen) == 0 )
			res ++;
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	int N;
	scanf("%d", &N);
	scanf("%s", pat);
	patLen = strlen(pat);
	for ( int i = 1; i <= N; i ++ ) {
		int m;
		int accSz = 0;
		scanf("%d", &m);
		for ( int j = 0; j < m; j ++ ) {
			static char ts[5];
			scanf("%s", ts);
			if ( ts[0] == 'a' || ts[0] == 'b' ) 
				acc[accSz++] = ts[0];
			else {
				int t;
				sscanf(ts, "%d", &t);
				memcpy(acc + accSz, comp[t], sizeof(char) * compSz[t]);
				accSz += compSz[t];
			}
		}

		compSz[i] = accSz;
		memcpy(comp[i], acc, sizeof(char) * accSz);
	}
	printf("%d\n", countMatch(comp[N], compSz[N]));
}
