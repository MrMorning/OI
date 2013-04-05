#include <cstdio>
#include <cstdlib>
int n, k, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &k, &seed);
	srand(seed);
	printf("20\n");
	for(int t = 0; t < 20; t ++){
		printf("%d\n%d ", n, k);
		for(int i = 0; i < k; i ++)
			printf("%d ", rand() % 15 + 1);
		printf("\n");
	}
}
