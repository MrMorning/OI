#include <cstdio>
#include <cstdlib>
int main(){
	freopen("t.in", "w", stdout);
	int T, N, seed;
	scanf("%d%d%d", &T, &N, &seed);
	srand(seed);
	printf("%d\n", T);
	while(T --){
		for(int i = 0; i < N; i ++)
			printf("%c", rand() % 3 + 'a');
		printf("\n");
	}
}
