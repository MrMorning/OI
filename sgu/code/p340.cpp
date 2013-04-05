#include <cstdio>
#include <cassert>
#include <cstring>
#include <cctype>

bool isoperator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

char ts[2000000], str[2000000];
char stk[2000000];

void printWord(int &i) {
	while ( isdigit(str[i]) || isalpha(str[i]) ) {
		if ( isdigit(str[i]) ) printf("%c", str[i]);
		else {
			printf("<i>");
			while ( isalpha(str[i]) )
				printf("%c", str[i++]);
			printf("</i>");
			i--;
		}
		i++;
	}
	i--;
}

int main() {
	freopen("t.in", "r", stdin);
	while ( gets(ts) ) {
		int m = strlen(ts), n = 0;
		for ( int i = 0; i < m; i ++ )
			if ( ts[i] != ' ' )
				str[n++] = ts[i];
		int top = 0;
		for ( int i = 1; i < n-1; i ++ ) {
				if ( isdigit(str[i]) || isalpha(str[i]) ) 
					printWord(i);
				else if ( str[i] == '(' || str[i] == ')' )
					putchar(str[i]);
				else if ( isoperator(str[i]) ) {
					printf("&nbsp;%c&nbsp;", str[i]);
				} else if ( str[i] == '_' ) {
					i++;
					if ( str[i] == '{' ) {
						printf("<sub>");
						stk[top++] = '_';
					} else {
						assert(isdigit(str[i]) || isalpha(str[i]));
						printf("<sub>");
						printWord(i);
						printf("</sub>");
					}
				} else if ( str[i] == '^' ) {
					i++;
					if ( str[i] == '{' ) {
						printf("<sup>");
						stk[top++] = '^';
					} else {
						assert(isdigit(str[i]) || isalpha(str[i]));
						printf("<sup>");
						printWord(i);
						printf("</sup>");
					}
				} else {
					assert(str[i] == '}');
					char ch = stk[--top];
					if ( ch == '^' )
						printf("</sup>");
					else
						printf("</sub>");
				}
			}
		puts("");
	}
}
