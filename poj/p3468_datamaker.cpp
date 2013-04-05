#include <cstdio>
#include <algorithm>
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define RANGE 1000
using namespace std;

int randval()
{
	return rand()%(2*RANGE)-RANGE;
}
int n,m,seed;
int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d",&n,&m,&seed);
	srand(seed);
	printf("%d %d\n",n,m);
	FOR(i,1,n)printf("%d ",randval());
	printf("\n");
	FOR(i,1,m)
	{
		int l,r;
		l=rand()%n+1; r=rand()%n+1;
		if(l>r)swap(l,r);
		bool opt=rand()%2;
		if(opt)printf("Q %d %d\n",l,r);
		else printf("C %d %d %d\n",l,r,randval());
	}

}
