#include <cstdio>
#include <cstring>
const int STR_MAX = 300010;
char input[40010][5];
int out[STR_MAX], nOut;
int N, M, K;
struct LoopQueue {
	int qh, qt;
	int ele[STR_MAX * 2];
	bool rev;
	void init() {
		rev = 0;
		qh = STR_MAX;
		qt = STR_MAX - 1;
	}
	void push(int val) {
		if ( !rev ) {
			if ( qt - qh + 1 == K ) 
				out[nOut++] = ele[qh++];
			ele[++qt] = val;
		} else {
			if ( qt - qh + 1 == K )
				out[nOut++] = ele[qt--];
			ele[--qh] = val;
		}
	}
	void reverse() {
		rev ^= 1;
	}
} LQ;

int conv(const char *s, int n) {
	int res = 0;
	for ( int i = n - 1; i >= 0; i -- )
		res = res * 256 + s[i];
	return res;
}

void printVal(int val) {
	if ( val % 256 )
		printf("%c", val % 256);
	if ( val / 256 % 256 )
		printf("%c", val / 256 % 256);
	if ( val / 256 / 256 % 256 )
		printf("%c", val / 256 / 256 % 256);
	puts("");
}

int main() {
	freopen("t.in", "r", stdin);
	LQ.init();
	scanf("%d%d%d", &N, &M, &K);
	if ( K == 0 )
		K = 1;
	for ( int i = 1; i <= N; i ++ ) 
		scanf("%s", input[i]);
	for ( int i = N; i >= 1; i -- )
		LQ.push(conv(input[i], strlen(input[i])));
	while ( M -- ) {
		static char ts[22];
		scanf("%s", ts);
		if ( ts[0] == 'A' ) {
			int end = 0;
			for ( end = 4; ts[end] != ')'; end ++ );
			LQ.push(conv(ts + 4, end - 4));
		} else 
			LQ.reverse();
	}
	while ( 1 ) {
		const int extraVal = conv("$$$", 3);
		LQ.push(extraVal);
		if ( out[nOut - 1] == extraVal )
			break;
	}
	for ( int i = nOut - 2; i >= 0; i -- )
		printVal(out[i]);
}
