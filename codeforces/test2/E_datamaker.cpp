#include <cstdio>
#include <cstdlib>
int n, m, k, seed;
bool e[5000][5000];
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &seed);
	srand(seed);
	printf("%d %d %d\n", n, m, k);
	while(m --){
		int x = rand() % n,
			y = rand() % n;
		while(x == y || e[x][y]){
			x = rand() % n;
			y = rand() % n;
		}
		e[x][y] = e[y][x] = true;
		printf("%d %d %d\n", x + 1, y + 1, rand() % 100000 + 1);
	}
}
