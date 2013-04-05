#include <cstdio>
#include <cstdlib>
int n, m, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	while(m --){
		printf("%c%c\n", rand() % n + 'A' ,rand() % 8 + 'A');
	}
}
