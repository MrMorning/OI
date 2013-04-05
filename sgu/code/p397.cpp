#include <cstdio>
#include <cstring>
const int kLenMax = 1000010;
struct Link {
	char ch;
	Link *next, *prev;
} *head, memo[kLenMax];
Link *alloc() {
	static int freepos = 0;
	return &memo[freepos++];
}
char cmd[kLenMax];
int ncmd;
int main() {
	scanf("%s", cmd);
	ncmd = strlen(cmd);

	head = alloc();
	head->ch = '$';

	Link *cur = head;
	for ( int i = 0; i < ncmd; i ++ ) {
		if ( cmd[i] == 'L' ) {
			if ( cur->prev )
				cur = cur->prev;
		} else if ( cmd[i] == 'R' ) {
			if ( cur->next )
				cur = cur->next;
		} else {
			Link *x = alloc();
			if ( cur->next )
				cur->next->prev = x;
			x->next = cur->next;
			x->prev = cur;
			x->ch = cmd[i];
			cur->next = x;
			cur = x;
		}
	}

	cur = head;
	while ( cur->next ) {
		cur = cur->next;
		putchar(cur->ch);
	}
    printf ("\n");
}
