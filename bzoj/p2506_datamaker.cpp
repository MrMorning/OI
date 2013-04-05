#include <cstdio>
#include <cstdlib>
#define RANGE 10000
int N, M, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &N, &M, &seed);
	srand(seed);
	printf("%d %d\n", N, M);
	for(int i = 0; i < N; i ++)
		printf("%d ", rand() % RANGE + 1);
	puts("");
	for(int i = 0; i < M; i ++){
		int p = rand() % (RANGE - 1) + 1;
		int l = rand() % N + 1, r = rand() % N + 1;
		if(l > r){
			l ^= r;
			r ^= l;
			l ^= r;
		}
		printf("%d %d %d %d\n", l, r, p, rand() % p);
	}
}
