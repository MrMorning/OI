#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int len, seed;
int a[2000000];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &len, &seed);
	srand(seed);
	int n = 0;
	while ( len ) {
		a[n ++] = rand() % min(len, 50) + 1;
		len -= a[n - 1];
	}
	printf("%d\n", n);
	for ( int i = 0; i < n; i ++ ) {
		printf("%d ", a[i]);
		for ( int j = 0; j < a[i]; j ++ )
			printf("%c", rand() % 5 + 'a');
		puts("");
	}
}
