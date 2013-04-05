#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int nword;
char word[33][35], invword[15][35], wordtmp[33][35];
bool useless[15];
int len[33];
int common[33][33];
int f[1 << 14][33], g[1 << 14][33];

int countCommon(int i, int j) {
	int n = len[i], m = len[j];
	for ( int st = max(0, n - m); st < n; st ++ ) {
		bool fail = false;
		for ( int k = 0; k < n - st; k ++ )
			if ( word[i][st + k] != word[j][k] ) {
				fail = true;
				break;
			}
		if ( !fail )
			return n - st;
	}
	return 0;
}

int inverse(int i) {
	return i < nword ? i + nword : i - nword;
}

int countbit(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}

void output(int s, int i) {
	if ( countbit(s) == 1 ) {
		for ( int k = 0; k < len[i]; k ++ )
			printf("%c", word[i][k]);
		for ( int k = common[i][inverse(i)]; k < len[i]; k ++ )
			printf("%c", word[inverse(i)][k]);
		return;
	}
	int t = g[s][i];
	for ( int k = 0; k < len[i] - common[i][t]; k ++ )
		printf("%c", word[i][k]);
	output(s - (1 << (i % nword)), t);
	for ( int k = len[i] - common[i][t] - 1; k >= 0; k -- )
		printf("%c", word[i][k]);
}

struct DisjointSet {
	int p[15];
	void init(int n) {
		for ( int i = 0; i < n; i ++ )
			p[i] = i;
	}
	int find(int i) {
		return p[i] == i ? i : p[i] = find(p[i]);
	}
	void merge(int i, int j) {
		i = find(i), j = find(j);
		if ( i != j )
			p[i] = j;
	}
} dset;

int main() {
	freopen("t.in", "r", stdin);

	scanf("%d", &nword);
	for ( int i = 0; i < nword; i ++ ) 
		scanf("%s", word[i]);

	dset.init(nword);
	for ( int i = 0; i < nword; i ++ ) 
		for ( int j = i + 1; j < nword; j ++ )
			if ( strlen(word[i]) == strlen(word[j]) && strstr(word[i], word[j]) ) 
				dset.merge(i, j);

	for ( int i = 0; i < nword; i ++ ) {
		memcpy(invword[i], word[i], sizeof(word[i]));
		int n = strlen(word[i]);
		for ( int k = 0; k < n / 2; k ++ )
			swap(invword[i][k], invword[i][n - k - 1]);
	}
	for ( int i = 0; i < nword; i ++ )
		for ( int j = 0; j < nword; j ++ )
			if ( strlen(word[i]) != strlen(word[j]) && (strstr(word[j], word[i]) || strstr(invword[j], word[i])) ) {
				useless[i] = true;
				break;
			}
	int nwordtmp = 0;
	for ( int i = 0; i < nword; i ++ )
		if ( !useless[i] && dset.find(i) == i ) 
			memcpy(wordtmp[nwordtmp++], word[i], sizeof(word[i]));
	nword = nwordtmp;
	memcpy(word, wordtmp, sizeof(wordtmp));

	for ( int i = 0; i < nword; i ++ ) {
		memcpy(word[nword + i], word[i], sizeof(word[i]));
		int n = strlen(word[i]);
		for ( int j = 0; j < n / 2; j ++ )
			swap(word[nword + i][j], word[nword + i][n - j - 1]);
	}
	for ( int i = 0; i < 2 * nword; i ++ )
		len[i] = strlen(word[i]);
	for ( int i = 0; i < 2 * nword; i ++ )
		for ( int j = 0; j < 2 * nword; j ++ ) 
			common[i][j] = countCommon(i, j);
	memset(f, 0x3f, sizeof(f));
	memset(g, -1, sizeof(g));
	for ( int i = 0; i < 2 * nword; i ++ ) {
		if ( i < nword )
			f[1 << i][i] = len[i] * 2 - common[i][i + nword];
		else
			f[1 << (i-nword)][i] = len[i] * 2 - common[i][i - nword]; 
	}
	int upperlim = 1 << nword;
	for ( int s = 1; s < upperlim; s ++ ) 
		for ( int i = 0; i < 2 * nword; i ++ ) 
			if ( f[s][i] != inf ) {
				for ( int j = 0; j < 2 * nword; j ++ )
					if ( !(s & (1 << (j % nword)))) {
						int ns = s | (1 << (j % nword));
						int nval = f[s][i] + 2 * (len[j] - common[j][i]);
						if ( f[ns][j] > nval ) {
							f[ns][j] = nval;
							g[ns][j] = i;
						}
					}
			}
	int ans = inf, best = -1;
	for ( int i = 0; i < 2 * nword; i ++ ) 
		if ( f[upperlim - 1][i] < ans ) {
			ans = f[upperlim - 1][i];
			best = i;
		}
	output(upperlim - 1, best);
}
