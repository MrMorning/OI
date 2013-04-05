#include<stdio.h>
#include<memory.h>

bool a[155][15];
int dp[2][60000];
int n,m,k;
int s[15];
int p[15];
int q[15];

void dfs(int i,int j,int cnt,int x){
	if(x>=m)return ;
	if(i>2&&x+1<=m&&p[x]==0&&p[x+1]==0&&!a[i][x]&&!a[i][x+1]){
		int t=j+s[x-1]*2+s[x]*2;
		if(dp[i%2][t]<cnt+1)dp[i%2][t]=cnt+1;
		dfs(i,t,cnt+1,x+2);
	}
	if(i>1&&x+2<=m&&p[x]<=1&&p[x+1]<=1&&p[x+2]<=1&&!a[i][x]&&!a[i][x+1]&&!a[i][x+2]){
		int t=j+s[x-1]*2+s[x]*2+s[x+1]*2;
		if(dp[i%2][t]<cnt+1)dp[i%2][t]=cnt+1;
		dfs(i,t,cnt+1,x+3);
	}
	dfs(i,j,cnt,x+1);
}
void solve(){
	int i,j;
	for(j=0;j<s[m];j++)dp[0][j]=-1;
	dp[0][s[m]-1]=0;
	for(i=1;i<=n;i++){
		for(j=0;j<s[m];j++)dp[i%2][j]=-1;
		for(j=0;j<s[m];j++){
			if(dp[(i-1)%2][j]!=-1){
				int cur=0;
				int kk=j;
				for(int t=1;t<=m;t++){
					q[t]=p[t]=kk%3;
					kk=kk/3;
					if(q[t]==0||q[t]==1){
						if(a[i][t])q[t]=2;
						else q[t]=0;
					}
					else {
						if(a[i][t])q[t]=2;
						else q[t]=1;
					}
				}
				for(int t=m;t>0;t--)cur=cur*3+q[t];
				if(dp[i%2][cur]<dp[(i-1)%2][j])dp[i%2][cur]=dp[(i-1)%2][j];//此处导致WA一天，dp[i%2][cur]此时不一定是-1的
				dfs(i,cur,dp[(i-1)%2][j],1);
			}
		}
	}
	int ans=0;
	int t1=n%2;
	for(j=0;j<s[m];j++){
		if(ans<dp[t1][j])ans=dp[t1][j];
	}
	printf("%d\n",ans);
}
int main(){
	freopen("t.in", "r", stdin);
	int t;
	scanf("%d",&t);
	s[0]=1;
	for(int i=1;i<12;i++)s[i]=s[i-1]*3;
	while(t--){
		memset(a,false,sizeof(a));
		scanf("%d%d%d",&n,&m,&k);
		int i,x,y;
		for(i=0;i<k;i++){
			scanf("%d%d",&x,&y);
			a[x][y]=true;
		}
		solve();
	}
	return 0;
}
