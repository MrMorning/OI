#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define RANDVAL rand()%20000-10000

using namespace std;

int N,M,seed;

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d",&N,&M,&seed);
	srand(seed);
	printf("%d\n",N);
	for(int i=1;i<=N;i++)
		printf("%d ",RANDVAL);
	printf("\n%d\n",M);
	for(int i = 1; i<= M;i++)
	{
		int opt=rand()%2;
		if(opt)
		{
			int l=rand()%N+1;
			int r=rand()%N+1;
			if(r<l) swap(l,r);
			printf("%d %d %d\n",opt,l,r);
		}
		else
			printf("%d %d %d\n",opt,rand()%N+1,RANDVAL);
	}
}
