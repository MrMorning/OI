#include <cstdio>
#include <cstdlib>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	printf("%d\n", n);
	while(n --)
	{
		int t = rand() % 2;
		if(t == 0)
			printf("I %d %d %s %d %d\n", rand() % 10, rand() % 10, rand() % rand() % 2 ? "M" : "F", rand() % 80 + 10, rand() % 100);
		else
			printf("Q %d %d %s %d\n", rand() % 10, -1, rand() % rand() % 2 ? "M" : "F", rand() % 80 + 10);
	}
}
