#include <cstdio>
#include <cassert>
#include <cctype>
#include <cstring>

#define SUS 0
#define PLU 1
#define MUL 2
#define SIN 3

int nDef;
char def[111][111];
int st1[111], st2[111], len1[111], len2[111];
int memo[111];

bool isOpr(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int findDef(char *s, int len) {
	for ( int i = 0; i < nDef; i ++ )
		if ( strncmp(s, def[i] + st1[i], len) == 0 
				&& def[i][st1[i]+len] == ' ' ) return i;
	return -1;
}

int work(char *s, int len) {
	int a[55], b[55];
	int na = 0, nb = 0;
	for ( int i = 0; i < len; i ++ ) {
		while ( s[i] == ' ' && i < len ) i ++;
		if ( i == len ) break;
		if ( isdigit(s[i]) ) {
			while ( i+1 < len && isdigit(s[i+1]) ) i++;
			a[na++] = SIN;
		} else if ( isalpha(s[i]) ) {
			int st = i;
			while ( i+1 < len && isalpha(s[i+1]) ) i++;
			int res = findDef(s + st, i-st+1);
			if ( res == -1 ) a[na++] = SIN;
			else a[na++] = memo[res];
		} else if ( s[i] == '(' ) {
			int st = i;
			int top = 1;
			while ( top ) {
				i++;
				if ( s[i] == '(' ) top++;
				else if ( s[i] == ')' ) top--;
			}
			if ( work(s+st+1, i-st-1) == SUS ) return SUS;
			a[na++] = SIN;
		} else {
			assert(isOpr(s[i]));
			b[nb++] = s[i];
		}
	}
	if ( nb == na ) {
		assert(b[0] == '-');
		memmove(a+1,a,sizeof(a[0])*na);
		a[0] = SIN;
	}

	for ( int i = 0; i < na; i ++ )
		if ( a[i] == SUS ) return SUS;
	if ( nb == 0 ) return SIN;
	for ( int i = 0; i < nb; i ++ ) 
		if ( b[i] == '*' ) {
			if ( a[i] == PLU || a[i+1] == PLU ) return SUS;
			a[i+1] = MUL;
		} else if ( b[i] == '/' ) {
			if ( a[i] == PLU || a[i+1] == PLU || a[i+1] == MUL ) return SUS;
			a[i+1] = MUL;
		} else if ( b[i] == '-' && a[i+1] == PLU ) return SUS;
	for ( int i = 0; i < nb; i ++ ) 
		if ( b[i] == '+' || b[i] == '-' ) return PLU;
	return MUL;
}

int main() {
	freopen("t.in", "r", stdin);
	int TST = 0;
	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d\n", &nDef);
		for ( int i = 0; i < nDef; i ++ ) {
			gets(def[i]);
			if ( def[i][strlen(def[i])-1] == '\r' ) def[i][strlen(def[i])-1] = 0;
			for ( st1[i] = strstr(def[i], "define") - def[i] + 6; def[i][st1[i]] == ' '; st1[i] ++ );
			for ( len1[i] = 0; isalpha(def[i][st1[i]+len1[i]]); len1[i]++ );
			for ( st2[i] = st1[i]+len1[i]; def[i][st2[i]] == ' '; st2[i]++ );
			len2[i] = strlen(def[i]) - st2[i];
			memo[i] = work(def[i]+st2[i], len2[i]);
		}
		static char req[111];
		gets(req);
		if ( req[strlen(req)-1] == '\r' ) req[strlen(req)-1] = 0;
		printf("%s\n", work(req, strlen(req)) == SUS ? "Suspicious" : "OK");
	}
}
