#include <cstdio>
#include <cstdlib>
int n, m, seed;
void pchar() {
	int t = rand() % 1000;
	static int cnt1 = 0, cnt2 = 0;
	if ( cnt1 < 10 && t == 0 ) {
		printf("?");
		cnt1 ++;
	}
	else if ( cnt2 < 10 && t == 1 ) {
		printf("*");
		cnt2 ++;
	}
	else 
		printf("%c", rand() % 26 + 'a');
}
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	while ( n -- )
		printf("%c", rand() % 26 + 'a');
	puts("");
	while ( m -- )
		pchar();
}
