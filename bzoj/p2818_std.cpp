#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
const int fin=1,maxn=10000001;
int N,tot;
int pr[maxn];
bool flag[maxn];
long long f[maxn];

  int main(){
  if(fin){
    freopen("t.in","r",stdin);
  }
  scanf("%d",&N);
  int i,j;
  long long ans=0;
  for(i=2;i<=N;++i){
    if(!flag[i]){
      pr[tot++]=i;
      f[i]=i-1;
    }
    for(j=0;j<tot&&i*pr[j]<=N;++j){
      flag[i*pr[j]]=true;
      if(i%pr[j]==0){
        f[i*pr[j]]=f[i]*pr[j];
        break;
      }else
        f[i*pr[j]]=f[i]*(pr[j]-1);
    }
  }
  for(i=2;i<=N;++i)f[i]+=f[i-1];
  for(i=1;i<=N;++i)f[i]=1+(f[i]<<1);
  for(i=0;i<tot;++i)ans+=f[N/pr[i]];
  printf("%lld",ans);
  if(fin){
    fclose(stdin); fclose(stdout);
  }
  return 0;
}
