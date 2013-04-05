#include <cstdio>
#include <cstdlib>
int N, K, seed;

int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &N, &K, &seed);
	srand(seed);
	printf("1\n");
	for(int t = 0; t < 1; t ++){
		printf("%d\n%d\n", N, K);
		for(int i = 0; i < N; i ++)
			printf("%d ", rand() % 1000000000);
	}
}
