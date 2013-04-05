#include <cstdio>
#include <cstdlib>
int n, m, k, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &seed);
	srand(seed);
	printf("%d %d %d\n", n, n - 1, k);
	int src = rand() % n, des = rand() % n;
	while ( src == des ) 
		src = rand() % n, des = rand() % n;
	printf("%d %d\n", src + 1, des + 1);
	
/*	while ( m -- ) {
		int a = rand() % n, b = rand() % n;
		while ( a == b )
			a = rand() % n, b = rand() % n;
		printf("%d %d %d\n", a + 1, b + 1, rand() % 1000 + 1);
	}*/
	for ( int i = 0; i < n - 1; i ++ ) 
		printf("%d %d %d\n", i + 1, i + 2, 1000);
	/*for ( int i = 0; i < m - (n - 1); i ++ ) {
		int a = rand() % n, b = rand() % n;
		while ( a > b )
			a = rand() % n, b = rand() % n;
		printf("%d %d %d\n", a + 1, b + 1, n + rand() % 1000 + 1);
	}*/
	printf("%d %d %d\n", n, 1, 1000);
}
