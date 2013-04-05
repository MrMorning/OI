#include <stdio.h>
long t,m;
long prime[101]={0};
int a[101][101]={0};
void shax(){
     long i,j;
     char ok[1001]={0};
     for(i=2;;i++){
      if(ok[i]==0) prime[++prime[0]]=i;
      if(prime[0]==t) break;
      for(j=i+i;j<=1000;j+=i) ok[j]=1;
     }
}
void read(){
     long i,j,x,k;
     for(i=1;i<=m;i++){
        scanf("%ld",&x);
        for(j=1;j<=t;j++){
         k=0; while(x%prime[j]==0) {x/=prime[j];k++;} k=k&1;
         a[i][j]=k;
        }
     }
}
int adjust(long x,long y){
     long i,j,k,tmp;
     for(j=y;j>=1;j--)
      for(i=x;i<=m;i++)
       if(a[i][j]){
        for(k=1;k<=m;k++){tmp=a[k][y];a[k][y]=a[k][j];a[k][j]=tmp;}
        for(k=1;k<=t;k++){tmp=a[x][k];a[x][k]=a[i][k];a[i][k]=tmp;}
        return 1;
       }
     return 0;
}
void Erase(long x,long y){
    long i,j,k;
    for(j=y-1;j>=1;j--){
     if(a[x][j])                   
      for(i=x;i<=m;i++){
       a[i][j]=a[i][j]^a[i][y];
      }
    }
}
long ans[1000]={0};
void out(long x){
     long i,j;
     ans[0]=1; ans[1]=1;
     for(i=1;i<=x;i++){
      for(j=1;j<=ans[0];j++)
       ans[j]*=2;
      for(j=1;j<=ans[0];j++){
       ans[j+1]+=ans[j]/10;
       ans[j]%=10;
      }
      while(ans[ans[0]+1]){
       ans[0]++;
       ans[ans[0]+1]+=ans[ans[0]]/10;
       ans[ans[0]]%=10;
      }
     }
     ans[1]--;
     for(i=1;i<=ans[0];i++){
      if(ans[i]<0){
       ans[i]+=10;
       ans[i+1]--;
      }
     }
     while(ans[ans[0]]==0&&ans[0]>1) ans[0]--;
     for(i=ans[0];i>=1;i--) printf("%ld",ans[i]);
     printf("\n");
}
void work(){
     long i,j;
     for(i=1,j=t;j>=1;i++,j--){
      if(a[i][j]==0) 
       if(!adjust(i,j)) break;
       Erase(i,j); 
     }
     i=m-i+1;
     out(i);
}
int main(){
	freopen("t.in", "r", stdin);
    scanf("%ld%ld",&t,&m);
    shax();
    read();
    work();
    return 0;
}
