#include <cstdio>
#include <cstdlib>

int c, seed, n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &c, &n, &seed);
	printf("%d\n", c);
	srand(seed);
	for(int i = 1; i <= n; i ++)
	{
		int ctrl = rand() % 3;
		if(ctrl == 0) printf("Ask ");
		else if(ctrl == 1) printf("Close ");
		else printf("Open ");
		if(ctrl == 0)
			printf("%d %d %d %d\n", rand() % 2 + 1, rand() % c + 1, rand() % 2 + 1, rand() % c + 1);
		else{
			int rc = rand() % c + 1, rr = rand() % 2 + 1;
			int rt = rand() % 2;
			if(rt == 0)
				printf("%d %d %d %d\n", rr, rc, 3 - rr, rc);
			else
				printf("%d %d %d %d\n", rr, rc, rr, rc + 1 > c ? rc - 1 : rc + 1);
		}
	}
	printf("Exit\n");
}
