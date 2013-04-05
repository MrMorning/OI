#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define RANG 10000
#define FOR(i,s,t) for(int i=s;i<=t;i++)

using namespace std;
int n,m,seed,testnum;

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d%d",&testnum,&n,&m,&seed);
	printf("%d\n",testnum);
	srand(seed);
	while(testnum--)
	{
		printf("%d\n",n);
		FOR(i,1,n)printf("%d ",rand()%(2*RANG)-RANG);
		printf("\n%d\n",m);
		FOR(i,1,m)
		{
			int x1=rand()%n+1;
			int y1=rand()%n+1;
			int x2=rand()%n+1;
			int y2=rand()%n+1;
			if(x1>x2)swap(x1,x2);
			if(y1>y2)swap(y1,y2);
			if(x1>y1)swap(x1,y1);
			if(x2>y2)swap(x2,y2);
			printf("%d %d %d %d\n",x1,y1,x2,y2);
		}
	}
}
