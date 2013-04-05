#include <cstdio>
#define MAXN 10100
#define FOR(i,s,t) for(int i=s;i<=t;i++)
int n,m,A[MAXN];

inline int max(int a,int b)
{return a>b?a:b;}

int main()
{
	freopen("t.in","r",stdin);
	int testnum;
	scanf("%d",&testnum);
	while(testnum--)
	{
		scanf("%d",&n);
		FOR(i,1,n)scanf("%d",&A[i]);
		scanf("%d",&m);
		FOR(i,1,m)
		{
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			int ans=-0x3f3f3f3f;
			FOR(s,x1,y1)
				FOR(t,x2,y2)
				{
					int cnt=0;
					if(s>t)continue;
					FOR(k,s,t)cnt+=A[k];
					ans=max(cnt,ans);
				}
			printf("%d\n",ans);
		}
	}
}
