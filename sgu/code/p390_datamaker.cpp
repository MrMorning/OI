#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, k, seed;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	srand(seed);
	int l = rand()%n+1, r = rand()%n+1;
	if ( l > r )
		swap(l, r);
	printf("%d %d %d\n", l, r, k);
}
