#include <cstdlib>
#include <cstdio>
int n, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	int pre = -1;
	for ( int i = 0; i < n; i ++ ) {
		int t = rand() % 3;
		if ( t == 0 ) putchar('+');
		else if ( t == 1 ) putchar('1');
		else {
			if ( pre == 1 ) putchar('*');
			else {
				putchar('1');
			}
		}
		pre = t;
	}
}
