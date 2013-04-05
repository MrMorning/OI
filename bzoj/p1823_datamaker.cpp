#include <cstdio>
#include <cstdlib>
int n_test, seed, n, m;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d%d", &n_test, &n, &m, &seed);
	srand(seed);
	printf("%d\n", n_test);
	while(n_test --)
	{
		printf("%d %d\n", n, m);
		for(int i = 0; i < m; i ++)
		{
			int s1 = rand() % 2, s2 = rand() % 2,
				t1 = rand() % n + 1, t2 = rand() % n + 1;
			printf("%c%d %c%d\n", s1 == 0 ? 'h' : 'm', t1,
					s2 == 0 ? 'h' : 'm', t2);
		}
	}
}
