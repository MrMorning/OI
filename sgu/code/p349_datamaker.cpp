#include <cstdio>
#include <cstdlib>
const int range = 100;
int N, M, seed;

void printWolf() {
	printf("%d %d %d %d\n", rand()%range-rand()%range, rand()%range+1,
			rand()%range-rand()%range, rand()%range+1);
}
void printSheep() {
	int x = rand()%range-rand()%range,
		y = rand()%range+2;
	printf("%d %d %d %d\n", x, y, x+rand()%2-rand()%2, y+rand()%2-rand()%2);
}


int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &N, &M, &seed);
	srand(seed);
	printf("%d %d\n", N, M);
	for ( int i = 0; i < N; i ++ )
		printWolf();
	for ( int i = 0; i < M; i ++ )
		printSheep();
}
