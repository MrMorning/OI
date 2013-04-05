#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	while(n --)
	{
		int t = rand() % 10;
		if(t == 0)
			printf("?");
		else if(t == 1)
			printf("*");
		else
			printf("%c", 'a' + rand() % 26);
	}
}
