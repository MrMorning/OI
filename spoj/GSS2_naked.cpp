#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define MAXN 100010
#define INF 0x3f3f3f3f
#define UNDEF -INF

using namespace std;

int n,m,A[MAXN];
bool e[MAXN*2];

int main()
{
	freopen("t.in","r",stdin);
	scanf("%d",&n);
	FOR(i,1,n)
		scanf("%d",&A[i]);
	scanf("%d",&m);
	FOR(i,1,m)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		int ans=UNDEF,cnt=0;
		FOR(s,a,b)
			FOR(t,s,b)
			{
				memset(e,0,sizeof(e));
				cnt=0;
				FOR(j,s,t)
				{
					if(!e[10000+A[j]]) 
					{
						cnt+=A[j];
						e[10000+A[j]]=true;
					}
				}
				ans=max(ans,cnt);
			}
		printf("%d\n",ans);
	}
}
