#include <cstdio>
#include <cstdlib>
#include <cstring>
const int N=1000005;
struct gtp{int y,next;}g[N*2];
int n,e;
int a[N*2][2],v[N*2],ls[10005],link[N*2];

inline void addedge(int x,int y){
       e++;
       g[e].y=y; g[e].next=ls[x]; ls[x]=e;
}

bool find(int p,int kk){
     int q;
     for (int t=ls[p];t;t=g[t].next)
       if (v[g[t].y]!=kk){
         v[g[t].y]=kk;
         q=link[g[t].y];
         link[g[t].y]=p;
         if (!q || find(q,kk)) return true;
         link[g[t].y]=q;
       }
     return false;
}

void solve(){
     e=0; memset(ls,0,sizeof(ls));
     for (int i=1;i<=n;i++){
       addedge(a[i][0],i);
       addedge(a[i][1],i);
     }
     for (int i=1;i<=10001;i++){
         if (!find(i,i)){
           printf("%d\n",i-1);
           return;
         }
     }
}

int main(){
	freopen("t.in", "r", stdin);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
      scanf("%d%d",&a[i][0],&a[i][1]);
    solve();
}
