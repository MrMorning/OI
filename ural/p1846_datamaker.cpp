#include <cstdio>
#include <cstdlib>
int n, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	printf("%d\n", n);
	while(n --)
		printf("%c %d\n", 1 ? '+' : '-', rand() % 1000000000 + 1);
}
