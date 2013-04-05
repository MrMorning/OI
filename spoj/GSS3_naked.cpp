#include <cstdio>
#include <algorithm>
#define MAXN 50000
#define FOR(i,s,t) for(int i=s;i<=t;i++)

using namespace std;

int N,M,A[MAXN];

int main()
{
	freopen("t.in","r",stdin);
	scanf("%d",&N);
	FOR(i,1,N)scanf("%d",&A[i]); 
	scanf("%d",&M);
	while(M--)
	{
		int k,x,y;
		scanf("%d%d%d",&k,&x,&y);
		if(k==0)
			A[x]=y;
		else
		{
			int ans=-0x3f3f3f3f;
			FOR(i,x,y)
				FOR(j,i,y)
				{
					int cnt=0;
					FOR(k,i,j)
						cnt+=A[k];
					ans=max(ans,cnt);
				}
			printf("%d\n",ans);
		}
	}
}
