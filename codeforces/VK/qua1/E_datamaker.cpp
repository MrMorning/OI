#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, k, seed;
int a[4000];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	srand(seed);
	for ( int i = 0; i < n; i ++ )
		a[i] = rand() % (86400 - 1) + 1;
	sort(a, a + n);
	n = unique(a, a + n) - a;
	k = min(n, k);
	printf("%d %d\n",n, k);
	for ( int i = 0; i < n; i ++ )
		printf("%d %d\n", a[i], rand() % (86400 - 1) + 1);
}
