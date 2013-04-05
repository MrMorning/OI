#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int N, M, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &N, &M, &seed);
	srand(seed);
	printf("%d %d\n", N, M);
	while ( M -- ) {
		int u = rand() % N + 1, v = rand() % N + 1;
		while ( u == v ) {
			u = rand() % N + 1,
			  v = rand() % N + 1;
		}
		if ( u > v )
			swap(u, v);
		printf("%d %d\n", u, v);
	}
}
