#include <stdio.h>
#include <string.h>
const int MAXN=1024/5;

int cntofone[1024];
int poss[101][MAXN],possNum[101];
int f[101][MAXN][MAXN];
bool used[1024];
int n,m;
int upperlim;

void dfs(int r,int stat,int occ)//stat: 1:placed occ:soldiers 1:placed
{
	if (used[occ])
		return;
	else
		used[occ]=true;
	poss[r][++possNum[r]]=occ;
    int lim=(stat|occ)&upperlim;//1:placed
    int pos=(lim+1)&(~lim)&upperlim;//get the first 0
    while(lim<upperlim)
    {
        lim+=pos;
        dfs(r,upperlim&(stat|pos>>2|pos>>1|pos|pos<<1|pos<<2),upperlim&(occ|pos));
        pos=((lim+1)&(~lim))&upperlim;
    }
	//used[occ]=false;
}

void init()
{
    freopen("p1185.in","r",stdin);
    freopen("p1185.out","w",stdout);
    for(int i=0;i<1024;i++)
    {
        int x=i;
        x = (x & 0x55555555) + (x >> 1 & 0x55555555);
        x = (x & 0x33333333) + (x >> 2 & 0x33333333);
        x = (x & 0x0F0F0F0F) + (x >> 4 & 0x0F0F0F0F);
        x = (x & 0x00FF00FF) + (x >> 8 & 0x00FF00FF);
        x = (x & 0x0000FFFF) + (x >> 16 & 0x0000FFFF);
        cntofone[i]=x;
    }
    scanf("%d %d\n",&n,&m);
    upperlim=(1<<m)-1;
    for(int i=1;i<=n;i++)
    {
        int tmp=0;
        for(int j=1;j<=m;j++)
        {
            char ch;
            scanf("%c",&ch);
            if (ch=='P')
               tmp=tmp+(1<<(m-j));//1:can place
        }
        scanf("\n");
		memset(used,0,sizeof(used));
        dfs(i,(~tmp)&upperlim,0);
    }

}

void update(int &a,int b)
{
	if (a<b)
		a=b;
}

void solve()
{
	possNum[0]=1;
	poss[0][1]=0;
	for(int j=1;j<=possNum[1];j++)
		f[1][j][1]=cntofone[poss[1][j]];
	for(int i=2;i<=n;i++)
		for(int j=1;j<=possNum[i];j++)
			for(int k=1;k<=possNum[i-1];k++)
				for(int l=1;l<=possNum[i-2];l++)
					if(((poss[i-1][k]&poss[i-2][l])==0)&&((poss[i-1][k]|poss[i-2][l])&poss[i][j])==0)
					{
						update(f[i][j][k],f[i-1][k][l]+cntofone[poss[i][j]]);
					}
	int ans=0;
	for(int j=1;j<=possNum[n];j++)
		for(int k=1;k<=possNum[n-1];k++)
			update(ans,f[n][j][k]);
	printf("%d",ans);
}

int main()
{
    init();
    solve();
}
