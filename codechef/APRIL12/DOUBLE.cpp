#include <cstdio>

int main() {
	int TST, N;

	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d", &N);
		printf("%d\n", (N & 1) ? N - 1 : N);
	}
}
