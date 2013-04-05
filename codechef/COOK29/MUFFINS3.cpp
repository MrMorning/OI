#include <cstdio>

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) {
		int n;
		scanf("%d", &n);
		printf("%d\n", n/2+1);
	}
}
