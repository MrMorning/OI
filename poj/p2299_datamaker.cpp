#include <cstdio>
#include <cstdlib>
int n,seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d",&n,&seed);
	srand(seed);
	printf("%d\n", n);
	while(n --) printf("%d\n", rand()%99999999);
	printf("0");
}
