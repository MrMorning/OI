#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#define mn 200005
#define sqr(x) ((x)*(x))
using namespace std;
 
int Cases,n,tot,ans,x[mn],y[mn],pattern[mn],match[mn<<1],next[mn<<1];
 
int main(){
	freopen("t.in", "r", stdin);
    scanf("%d",&Cases);
    while(Cases--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
        x[n+1]=x[1],y[n+1]=y[1],x[n+2]=x[2],y[n+2]=y[2];
        tot=0,ans=0;
        for(int i=1;i<=n;i++){
            match[++tot]=sqr(x[i+1]-x[i])+sqr(y[i+1]-y[i]);
            match[++tot]=(x[i+1]-x[i])*(y[i+2]-y[i])-(y[i+1]-y[i])*(x[i+2]-x[i]);
        }
        for(int i=1;i<=tot;i++)
            pattern[tot-i+1]=match[i+tot]=match[i];
        memset(next,0,sizeof(next));
        for(int i=2,j=0;i<=tot;i++){
            while(j && pattern[j+1]!=pattern[i]) j=next[j];
            next[i]=(j+=(pattern[j+1]==pattern[i]));
        }
        for(int i=1,j=0;i<=(tot<<1);i++){
            while(j && pattern[j+1]!=match[i]) j=next[j];
            j+=(pattern[j+1]==match[i]);
            if(j==tot) ans++,j=next[j];
        }
        printf("%d\n",ans);
    }
    return 0;
}
