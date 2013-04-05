#include <cstdio>
#include <cstdlib>
int TST, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &TST, &seed);
	srand(seed);
	printf("%d\n", TST);
	while ( TST -- ) {
		int N = rand() % 100 + 1, M = rand() % 100000+1;
		int HP = rand() % 70+1, MP = rand() % 70+1,
			SP = rand() % 70+1;
		int DH = rand() % HP,
			DM = rand() % MP,
			DS = rand() % SP,
			X = rand() % 10000;
		printf("%d %d %d %d %d %d %d %d %d\n",
				N, M, HP, MP, SP, DH, DM, DS, X);
		for ( int i = 0; i < N; i ++ )
			printf("%d ", rand() % (HP+1));
		puts("");
		int N1 = rand() % 11, N2 = rand() % 11;
		printf("%d", N1);
		while ( N1 -- ) 
			printf(" %d %d", rand() % (MP+1), rand() % 10000);
		puts("");
		printf("%d", N2);
		while ( N2 -- ) 
			printf(" %d %d", rand() % (SP+1), rand() % 10000);
		puts("");
		puts("");
	}
}
