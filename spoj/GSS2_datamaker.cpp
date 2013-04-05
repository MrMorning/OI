#include <cstdio>
#include <algorithm>
#define RANG 100000
#define FOR(i,s,t) for(int i=s;i<=t;i++)

using namespace std;

int n,m,seed;

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d",&n,&m,&seed);
	srand(seed);
	printf("%d\n",n);
	FOR(i,1,n)printf("%d ",rand()%(2*RANG)-RANG);
	printf("\n%d\n",m);
	FOR(i,1,m)
	{
		int l=rand()%n+1;
		int r=rand()%n+1;
		if(l>r)swap(l,r);
		printf("%d %d\n",l,r);
	}
}
