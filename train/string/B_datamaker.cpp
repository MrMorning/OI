#include <cstdio>
#include <cstdlib>
int n, m, seed;
void pmask(int len) {
	for ( int i = 0; i < len; i ++ ) {
		int t = rand() % 4;
		if ( t < 2 )
			printf("%c", t + 'a');
		else if ( t == 2 )
			printf("?");
		else
			printf("*");
	}
	puts("");
}
void pstr(int len) {
	while ( len -- )
		printf("%c", rand() % 2 + 'a');
	puts("");
}

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for ( int i = 0; i < n; i ++ ) 
		pmask(rand() % 6 + 1);
	for ( int i = 0; i < m; i ++ )
		pstr(rand() % 20 + 1);
}
