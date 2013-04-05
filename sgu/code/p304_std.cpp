#include <stdio.h>
long n,k,p;
long f[601][601];
long s[601][601]; /*记录决策*/
long b[601];      /*cost_gum*/
long c[601];      /*cost_tee*/
long a[601];      /*belong*/
long d[601];
long pre[601]={0};/*前驱指针*/
void read(){
    long i;
    scanf("%ld%ld%ld",&n,&k,&p);
    for(i=1;i<=k;i++) scanf("%ld",&b[i]);
    for(i=1;i<=n;i++) scanf("%ld%ld",&c[i],&a[i]);
    for(i=1;i<=n;i++) d[i]=i;
}
void sort(){
    long i,j,k;
    for(i=1;i<=n;i++)
     for(j=i+1;j<=n;j++)
      if(a[i]>a[j]||(a[i]==a[j]&&c[i]<c[j])){
         k=a[i]; a[i]=a[j]; a[j]=k;
         k=c[i]; c[i]=c[j]; c[j]=k;
         k=d[i]; d[i]=d[j]; d[j]=k;
      }
    k=0;
    for(i=1;i<=n;i++){
        c[i]+=c[i-1];
        if(a[i]!=a[i-1]&&i>1) k=i-1;
        pre[i]=k;
    }
}
void dp(){
    long i,j,k,t;
    for(i=1;i<=n;i++) for(j=0;j<=i;j++){
       f[i][j]=99999999;
       for(k=pre[i];k<=i;k++){
         t=i-k;
         if(j>=t&&(j-t)<=pre[i]){
           if(f[pre[i]][j-t]+c[i]-c[k]+b[a[i]]*(k!=i)<f[i][j]){
            f[i][j]=f[pre[i]][j-t]+c[i]-c[k]+b[a[i]]*(k!=i);
            s[i][j]=k;
           }
         }
       }
    }
}
void write(long x,long y){
    long i;
    if(x==0) return;
    for(i=s[x][y]+1;i<=x;i++) printf("%ld ",d[i]);
    write(pre[x],y-(x-s[x][y]));
}
void out(){
    long i;
    for(i=n;i>0;i--)
      if(f[n][i]<=p){
       printf("%ld\n",i);
    //   write(n,i);
       return;
      }
    printf("0\n");
}
int main(){
	freopen("t.in", "r", stdin);
    read();
    sort();
    dp();
    out();
    return 0;
}
