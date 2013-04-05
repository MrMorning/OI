#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, seed, a[100010];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	for ( int i = 1; i <= n; i ++ )
		a[i] = i;
	random_shuffle(a+1, a+1+n);
	for ( int i = 1; i <= n; i ++ )
		printf("%d ", a[i]);
}
