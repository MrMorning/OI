#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int next[1002];
bool painted[1001];
int ops[5000][5];
int n,m,tot;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d",&n,&m);
	tot=n*n;
	for (int i=0;i<m;++i)
	{
		int x1,x2,y1,y2;
		char c;
		scanf("%d %d %d %d %c",&x1,&y1,&x2,&y2,&c);
		ops[i][0]=min(x1,x2); ops[i][2]=max(x1,x2);
		ops[i][1]=min(y1,y2); ops[i][3]=max(y1,y2);
		ops[i][4]=c=='b';
	}
	for (int i=1;i<=n;++i)
	{
		for (int j=0;j<=n;++j) next[j]=j+1; next[n+1]=n+1;
		memset(painted,false,sizeof(painted));
		for (int p=m-1;p>=0;--p) if (i>=ops[p][0] && i<=ops[p][2])
		{
			int s,j;
			for (j=ops[p][1];j<=ops[p][3];s=j,j=next[j],next[s]=next[ops[p][3]]) if (!painted[j])
			{
				tot-=ops[p][4];
				painted[j]=true;
			}
		}
	}
	printf("%d\n",tot);
	return 0;
}
