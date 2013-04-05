#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
struct node
{
	LL x,y;
}in,out,dp[20][200][1000];
LL x,y;
int dx[20],dy[20],nx,ny;
int K;

node dfs(int pos, int cnt ,bool low, bool inf, int rem)
{
	if (pos==-1)
	{
		if (rem>0) {in.x=0;in.y=(rem>=cnt)?rem-cnt:0;}
		else {in.x=1;in.y=K>cnt?K-cnt:0;}
		return in;
	}
	if (!low && !inf && dp[pos][cnt][rem].x!=-1) return dp[pos][cnt][rem];
	int st=low?dx[pos]:0;
	int end=inf?dy[pos]:9;
	int tr=rem;
	node ans;
	ans.x=0;ans.y=0;
	for (int i=st;i<=end;i++)
	{
		out=dfs(pos-1, cnt+i, low&&(i==dx[pos]), inf && (i==dy[pos]), tr);
		ans.x+=out.x;
		ans.y=out.y;
		tr=out.y;
	}
	if (!low && !inf) dp[pos][cnt][rem]=ans;
	return ans;
}

void solve(LL x,LL y)
{
	nx=ny=0;
	while(x>0)
	{
		dx[nx++]=x%10;
		x/=10;
	}
	while(y>0)
	{
		dy[ny++]=y%10;
		y/=10;
	}
	for (int i=nx;i<ny;i++)
	{
		dx[nx++]=0;
	}
	out=dfs(ny-1,0,1,1,0);
	if (out.y>0) out.x--;
	printf("%lld\n",out.x);
}

int main()
{
	freopen("t.in", "r", stdin);
	while(scanf("%lld%lld%d",&x,&y,&K)!=EOF)
	{
		memset(dp,-1,sizeof(dp));
		solve(x,y);
	}
	return 0;
}
