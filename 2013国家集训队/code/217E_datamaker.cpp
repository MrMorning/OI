#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

char CHR[4] = {'A', 'G', 'C', 'T'};
int len, k, n, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &len, &k, &n, &seed);
	srand(seed);
	for ( int i = 0; i < len; i ++ )
		printf("%c", CHR[rand()%4]);
	puts("");
	printf("%d\n%d\n", k, n);
	while ( n -- ) {
		int l = rand() % len+1, r = rand()%len+1;
		if ( l > r ) swap(l, r);
		printf("%d %d\n", l, r);
		len += r-l+1;
	}
}
