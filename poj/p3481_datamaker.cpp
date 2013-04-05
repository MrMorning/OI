#include <cstdio>
#include <cstdlib>
#define RANG 1000100

int m,n,seed;
bool exist[RANG*2];

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d",&m,&seed);
	srand(seed);
	while(m--)
	{
		int k=rand()%3+1;
		if(k==1)
		{
			int t=rand()%RANG+1;
			while(exist[t+1000000])t=rand()%RANG+1;
			exist[t+1000000]=true;
			n++;
			printf("%d %d %d\n",k,n,t);
		}
		else
		{
			printf("%d\n",k);
			//n>0?n--:n;
		}
	}
	printf("0\n");
}
