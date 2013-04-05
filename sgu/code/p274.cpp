#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;
bool done[111][111];

bool isLetter(const char *s, int l, int r) {
	if ( l != r )
		return false;
	return isalpha(s[l]);
}

bool isSymbol(const char *s, int l, int r) {
	if ( l != r )
		return false;
	return isLetter(s, l, r) || isdigit(s[l]) || s[l] == '_' || s[l] == '-';
}

bool isWord(const char *s, int l, int r) {
	if ( l > r )
		return false;
	return isSymbol(s, l, r) || (isSymbol(s, l, l) && isWord(s, l + 1, r));
}

bool isPrefix(const char *s, int l, int r) {
	static bool memo[111][111];
	if ( l > r )
		return false;
	if ( done[l][r] )
		return memo[l][r];
	done[l][r] = true;
	bool &ret = memo[l][r] = isWord(s, l, r);
	for ( int k = l; k <= r && !ret; k ++ )
		if ( s[k] == '.' ) {
			ret |= isPrefix(s, l, k - 1) && isWord(s, k + 1, r);
		}
	return ret;
}

bool isDomain(const char *s, int l, int r) {
	if ( l > r )
		return false;
	if ( r - l + 1 == 2 && isLetter(s, l, l) && isLetter(s, r, r) )
		return true;
	if ( r - l + 1 == 3 && isLetter(s, l, l) && isLetter(s, r - 1, r - 1) 
			&& isLetter(s, r, r) )
		return true;
	return false;
}

bool isSuffix(const char *s, int l, int r) {
	if ( l > r )
		return false;
	int ret = false;
	ret |= s[r - 2] == '.' && isPrefix(s, l, r - 3) && isDomain(s, r - 1, r);
	ret |= s[r - 3] == '.' && isPrefix(s, l, r - 4) && isDomain(s, r - 2, r);
	return ret;
}

bool isAddress(const char *s, int l, int r) {
	if ( l > r )
		return false;
	for ( int k = l; k <= r; k ++ )
		if ( s[k] == '@' ) 
			return isPrefix(s, l, k - 1) && isSuffix(s, k + 1, r);
	return false;
}

int main() {
	int TST;
	scanf("%d\n", &TST);
	while ( TST -- ) {
		memset(done, 0, sizeof(done));
		string ts;
		getline(cin, ts);
		int n = ts.size();
		if ( isAddress(ts.c_str(), 0, n - 1) )
			puts("YES");
		else
			puts("NO");
	}
}
