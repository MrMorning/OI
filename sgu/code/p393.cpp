#include<stdio.h>
#include<string.h>
char s[55][4];
char ans[20][20];
int d[20];
int n,m;
int a[20],sum[20];
int dfs(int dep,int maxdep){
    int i,j;
    int w1,w2;
    int flag=1;
    for (i=0;i<m;i++){
        for (j=i+1;j<m;j++){
            w1=a[s[i][0]-'a'+1];
            w2=a[s[j][0]-'a'+1];
            if (s[i][0]==s[j][0]||(w1==w2&&w1>0)){
                w1=a[s[i][1]-'a'+1];
                w2=a[s[j][1]-'a'+1];
                if (s[i][1]==s[j][1]||(w1==w2&&w1>0)){
                    flag=0;
                    break;
                }
            }
        }
        if (!flag) break;
    }
    if (!flag) return 0;
    if (dep>n) return 1;
    for (i=1;i<=maxdep;i++){
        a[dep]=i;
        sum[i]++;
        if (dfs(dep+1,maxdep)) return 1;
        a[dep]=0;
        sum[i]--;
        if (sum[i]==0) break;
    }
    return 0;
}
int main(){
    int i,k;
    while (scanf("%d%d",&n,&m)!=EOF){
        getchar();
        for (i=0;i<m;i++) gets(s[i]);
        memset(sum,0,sizeof(sum));
        a[1]=1;sum[1]=1;
        for (k=1;k<=n;k++)
            if (dfs(2,k)) break;
        printf("%d\n",k);
        memset(d,0,sizeof(d));
        for (i=1;i<=n;i++) ans[a[i]][d[a[i]]++]='a'+i-1;
        for (i=1;i<=k;i++) printf("%s\n",ans[i]);
    }
    return 0;
}
