#include <cstdio>
#define MAXN 101000
#define FOR(i,s,t) for(int i=s;i<=t;i++)
int n,m; 
long long A[MAXN];

int main()
{
	freopen("t.in","r",stdin);
	scanf("%d%d",&n,&m);
	FOR(i,1,n)scanf("%lld",&A[i]);
	FOR(i,1,m)
	{
		int a,b,x;
		char k;
		scanf("\n%c%d%d",&k,&a,&b);
		if(k=='C')
		{
			scanf("%d",&x);
			FOR(j,a,b) A[j]+=x;
		}else 
		{
			long long ans=0;
			FOR(j,a,b) ans+=A[j];
			printf("%lld\n",ans);
		}
	}
}
