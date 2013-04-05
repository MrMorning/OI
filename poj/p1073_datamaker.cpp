#include <cstdio>
#include <cstdlib>

int testnum,n,m,seed;

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d%d",&testnum,&n,&m,&seed);
	srand(seed);
	printf("%d\n",testnum);
	while(testnum --)
	{
		printf("%d %d\n",n,m);
		for(int i = 1; i <= m; i++)
		{
			int t = rand()%2;
			if(t)
				printf("D");
			else
				printf("A");
			int a = rand()%n+1;
			int b = rand()%n+1;
			while(a == b) b = rand()%n + 1;
		printf(" %d %d\n",a,b);
		}
	}
}
