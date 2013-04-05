#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define RANG 10000
#define FOR(i,s,t) for(int i = s; i <= t; i ++)
using namespace std;

const char MAP[4] = {'I','Q','D','R'};
int n,m,seed;

inline int randVal()
{return rand()%(RANG*2)-RANG;}

inline int randPos()
{return rand()%n+1;}

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d",&n,&m,&seed);
	srand(seed);
	printf("%d\n",n);
	FOR(i,1,n) printf("%d ",randVal());
	printf("\n%d\n",m);
	FOR(i,1,m)
	{
		char opt = MAP[rand()%4];
		int x = randPos();
		if(opt == 'I' || opt == 'R')
		{
			printf("%c %d %d\n",opt,x,randVal());
			if(opt == 'I') n++;
		}
		else if(opt == 'Q')
		{
			int r = randPos();
			if(x > r) swap(x, r);
			printf("Q %d %d\n",x,r);
		}
		else
			printf("D %d\n",x),n--;

	}
}
