#include <cstdio>
#include <cstdlib>
char RAND_CHAR[3] = {'L', 'R', 'B'};
int n, m, seed;
int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for (int i = 0; i < n; i ++)
		printf("%c", RAND_CHAR[rand() % 3]);
	puts("");
	printf("%d\n", m);
	for (int i = 1; i <= m; i ++) {
		int t = rand() % 2;
		printf("%d ", t);
		if (t == 0) {
			char ch = RAND_CHAR[rand() % 3];
			int p = rand() % n + 1;
			printf("%d %c\n", p, ch);
		}
		else {
			int l = rand() % n + 1;
			int r = rand() % (n + 2 - l) + l;
			printf("%d %d\n", l, r);
		}
	}
}
