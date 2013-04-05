#include <cstdio>
#include <algorithm>
using namespace std;
const int LIM = 1000000000;
int seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	int l1 = rand() % LIM + 1, l2 = rand() % LIM + 1,
		r1 = rand() % LIM + 1, r2 = rand() % LIM + 1;
	if ( l1 > r1 )
		swap(l1, r1);
	if ( l2 > r2 )
		swap(l2, r2);
	printf("%d %d %d %d\n", l1, r1, l2, r2);
}
