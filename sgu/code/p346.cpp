#include <cstdio>

int a[8], s;
char ch[3];

int main() {
	freopen("t.in", "r", stdin);
	for ( int i = 1; i <= 7; i ++ )
		scanf("%d\n", &a[i]);
	scanf("%s", ch);
	if ( ch[0] == 'N' ) {
		s = a[1] * 8;
		for ( int i = 2; i <= 7; i ++ )
			s = s + a[i] * i;
	} else if ( ch[0] == 'R' ) {
		s = 7;
		s = s + a[1] * 8;
		for ( int i = 2; i <= 7; i ++ )
			s = s + a[i] * i;
	} else {
		s = a[1] * 8;
		for ( int i = 2; i <= 7; i ++ )
			s = s + a[i] * i;
	}
	printf("%d\n", s);
}
