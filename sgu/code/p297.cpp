#include <cstdio>
int N, M;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	int tot = 0;
	while ( M -- ) {
		int x;
		scanf("%d", &x);
		tot += x;
	}
	printf("%d\n", tot % N);
}
