#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <cstdlib>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
int N, M, seed;
int kind[10010];
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &N, &M, &seed);
	srand(seed);
	printf("%d %d\n", N, M);
	while ( M -- )
		printf("%d %d\n", rand() % N + 1, rand() % N + 1);
	for ( int i = 1; i <= N; i ++ )
		kind[i] = rand() % 3;
	vector<int> A, B;
	for ( int i = 1; i <= N; i ++ ) {
		if ( kind[i] == 1 )
			A.push_back(i);
		if ( kind[i] == 2 )
			B.push_back(i);
	}
	printf("%d\n", A.size());
	foreach(it, A)
		printf("%d ", *it);
	puts("");
	printf("%d\n", B.size());
	foreach(it, B)
		printf("%d ", *it);
	puts("");
}
