#include <cstdio>
#include <cstring>
#include <cctype>
#define ORIGIN 0
#define UP 1
#define DOWN 2
char convert(char ch, int type) {
	if ( type == ORIGIN )
		return ch;
	int delta;
	if ( 'a' <= ch && ch <= 'z' )
		delta = ch - 'a';
	else
		delta = ch - 'A';	
	if ( type == UP )
		return delta + 'A';
	else
		return delta + 'a';
}
char str[1111];
int stk[1111];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	int len = strlen(str);
	int top = 0;
	stk[top++] = ORIGIN;
	for ( int i = 0; i < len; i ++ ) {
		if ( isalpha(str[i]) ) 
			printf("%c", convert(str[i], stk[top - 1]));
		else {
			if ( str[i + 2] == 'P' ) {
				stk[top++] = UP;
				i += 3;
			} else if ( str[i + 2] == 'O' ) {
				stk[top++] = DOWN;
				i += 5;
			} else if ( str[i + 2] == 'U' ) {
				--top;
				i += 4;
			} else if ( str[i + 2] == 'D' ) {
				--top;
				i += 6;
			}
		}
	}
}
