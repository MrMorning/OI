#include <cstdio>

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		int n;
		int sumA = 0, sumB = 0;
		scanf("%d", &n);
		for ( int i = 0; i< n; i ++ ) {
			int a, b;
			scanf("%d%d", &a, &b);
			sumA += a;
			sumB += b;
		}
		printf("%d\n", sumA-sumB);
	}
}
