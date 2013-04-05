#include <iostream>
#include <cstdio>
int ans,e[6001],f[6001],g[101][6001][2],m,n,q[6001],s[6001][26],t;
int main(){
   freopen("t.in","r",stdin);
   fscanf(stdin,"%d%d\n",&n,&m);
   for(int i=1;i<=n;i++){
      char ch;int k=0;
      do{
         fscanf(stdin,"%c",&ch);
         if(ch<65){e[k]=1;break;}
         else{if(!s[k][ch-65])s[k][ch-65]=++t;k=s[k][ch-65];}
      }while(1);
      fscanf(stdin,"\n");
   }
   f[0]=-1;
   for(int l=0,r=0;l<=r;l++){
      if(!e[q[l]]){
         int k=f[q[l]];while(k!=-1&&!e[k])k=f[k];
         if(k!=-1&&e[k])e[q[l]]=1;
      }
      for(int i=0;i<26;i++)
         if(s[q[l]][i]){
            int k=f[q[l]];while(k!=-1&&!s[k][i])k=f[k];
            if(k!=-1&&s[k][i])f[s[q[l]][i]]=s[k][i];
            q[++r]=s[q[l]][i];
         }else{
            int k=f[q[l]];while(k!=-1&&!s[k][i])k=f[k];
            if(k!=-1&&s[k][i])s[q[l]][i]=s[k][i];
         }
   }
   g[0][0][0]=1;
   for(int i=1,x;i<=m;i++)
      for(int j=0;j<=t;j++)
         for(int k=0;k<26;k++)
            for(int l=0;l<2;l++){
               if(e[s[j][k]])x=1;else x=l;
               g[i][s[j][k]][x]=(g[i][s[j][k]][x]+g[i-1][j][l])%10007;
            }
   for(int i=0;i<=t;i++)ans=(ans+g[m][i][1])%10007;
   fprintf(stdout,"%d\n",ans);
   return 0;
}
