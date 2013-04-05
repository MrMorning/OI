#include <cstdio>
#include <cstdlib>
int n, m, seed;

int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	while(n --)
		printf("%c", rand() % 2 ? 'F' : 'T');
	printf("\n%d\n", m);
}
