#include <cstdio>
#include <cstdlib>
int main(){
	int seed;
	scanf("%d", &seed);
	srand(seed);
	printf("10\n");
	for(int i = 0; i < 10; i ++){
		int t = rand() % 10;
		int x = t == 0 ? 1000000001 : 10000001;
		printf("%d %d %d\n", rand() % 1000000001, rand() % x, rand() % 10000000 + 1);
	}
}
