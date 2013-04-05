#include <cstdio>
#include <cstring>
#define N 5001
#define E 20001
struct gtp{int x,y,next;}g[E];
int n,e,ls[N],f[N],dep[N],color[N],list[N];

void init(){
    scanf("%d%d",&n,&e);
    memset(ls,0,sizeof(ls));
    for (int i=1;i<=e;i++){
        scanf("%d%d",&g[i].x,&g[i].y);
        g[i].next=ls[g[i].x];
        ls[g[i].x]=i;
    }    
}    

int gf(int k){
    if (f[k]==k) return k;
    f[k]=gf(f[k]);
    return f[k];
}    

void dfs(int k){
    for (int t=ls[k];t!=0;t=g[t].next)
      if (dep[g[t].y]==0){
          dep[g[t].y]=dep[k]+1;
          dfs(g[t].y);
          if (dep[gf(g[t].y)]<dep[gf(k)]) f[k]=f[g[t].y];
      }else  
      if (color[gf(g[t].y)]==0 && dep[gf(g[t].y)]<dep[gf(k)])
        f[k]=f[g[t].y];
   color[k]=1;
}    

void tarjan(){
    for (int i=1;i<=n;i++) f[i]=i;
    memset(dep,0,sizeof(dep));
    memset(color,0,sizeof(color));
    for (int i=1;i<=n;i++)
      if (dep[i]==0){
          dep[i]=1;
          dfs(i);
      }        
    for (int i=1;i<=n;i++) gf(i);
}    

void dfs2(int k){
    list[dep[k]]=f[k];
    for (int t=ls[k];t!=0;t=g[t].next)
      if (dep[g[t].y]==0) {
          dep[g[t].y]=dep[k];
          if (f[g[t].y]!=f[k]) dep[g[t].y]++;
          dfs2(g[t].y);
      }    
}    

bool flag(){
    int r[N];
    memset(r,0,sizeof(r));
    for (int i=1;i<=n;i++)
      for (int t=ls[i];t!=0;t=g[t].next)
        if (f[g[t].x]!=f[g[t].y]) r[f[g[t].y]]++;
    memset(dep,0,sizeof(dep));
    memset(list,0,sizeof(list));
    for (int i=1;i<=n;i++)
      if (f[i]==i && r[i]==0) {
          dep[i]=1;
          dfs2(i);
          break;
      }    
    for (int i=1;i<=n;i++)    
      if (dep[i]==0 || list[dep[i]]!=f[i]) return false;
    return true;
}

int main(){
	freopen("t.in", "r", stdin);
    int TC;
    scanf("%d",&TC);
    for (int i=0;i<TC;i++){
        init();
        tarjan();
        if (flag()) printf("Yes\n");
               else printf("No\n");
    }    
}
