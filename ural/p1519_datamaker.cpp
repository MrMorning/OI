#include <cstdio>
#include <cstdlib>
int seed, n, m;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; i ++, puts(""))
		for(int j = 0; j < m; j ++){
			int t = rand() % 3;
			if(t)
				printf(".");
			else
				printf("*");
		}
}
