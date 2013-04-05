#include <cstdio>
#include <cstdlib>

int main()
{
	int n, seed;
	freopen("t.in","w",stdout);
	scanf("%d%d",&n,&seed);
	srand(seed);
	printf("%d\n",n);
	for(int i = 1; i <=n; i ++)
	{
		int t = rand()%2;
		if(t) printf("M %d %d\n", rand()%30000 +1,rand()%30000+1);
		else
			printf("C %d\n",rand()%30000 +1);
	}
}
