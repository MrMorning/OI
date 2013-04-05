#include <cstdio>
int stk[50], top;
void solve(int n) {
	if ( n == 1 )
		return;
	int x = n / 2;
	if ( x % 2 == 0 ) {
		x ++;
		stk[top++] = 1;
	} else
		stk[top++] = 2;
	solve(x);
}
int main() {
	int n;
	scanf("%d", &n);
	if ( n % 2 == 0 ) {
		puts("No solution");
		return 0;
	}
	solve(n);
	printf("%d\n", top);
	while ( top ) 
		printf("%d ", stk[--top]);
}
