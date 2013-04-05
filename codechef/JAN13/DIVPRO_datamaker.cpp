#include <cstdio>
#include <cstdlib>
typedef long long ll;
const ll kLim = 1000000000000000000LL;
int TST, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &TST, &seed);
	srand(seed);
	printf("%d\n", TST);
	while ( TST -- ) {
		int n2 = rand() % 54, n3 = rand() % 36, n5 = rand() % 18, n7 = rand() % 18;
		int n = rand() % 36 + 1;
	   	ll res = 1;
		while ( n2 -- && res <= kLim / 2 ) res *= 2;
		while ( n3 -- && res <= kLim / 3 ) res *= 3;
		while ( n5 -- && res <= kLim / 5 ) res *= 5;
		while ( n7 -- && res <= kLim / 5 ) res *= 7;
		printf("%d %lld\n", n, res);
	}
}
