#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;

int N, M, Q, seed;
map<pair<int, int>, bool> done;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &N, &M, &Q, &seed);
	srand(seed);
	printf("%d %d %d\n", N, M, rand() % N);
	for ( int i = 0; i < min(M, N); i ++ ) {
		int a = i, b = rand() % N;
		while( a == b || done[make_pair(a, b)]) {
			b = rand() % N;
		}
		printf("%d %d\n", a, b);
		done[make_pair(a, b)] = true;
		done[make_pair(b, a)] = true;
	}
	for ( int i = N; i < M; i ++ ) {
		int a = rand() % N, b = rand() % N;
		while ( a == b || done[make_pair(a, b)]) {
			a = rand() % N, b = rand() % N;
		}
		done[make_pair(a, b)] = true;
		done[make_pair(b, a)] = true;
		printf("%d %d\n", a, b);
	}
	printf("%d\n", Q);
	while ( Q -- )
		printf("%d\n", rand() % 1000000000 + 1);
}
