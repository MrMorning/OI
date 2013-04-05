#include <iostream>
#include <cstdio>
#include <memory.h>
#include <algorithm>
#include <queue>
#include <set>
#include <cmath>
#include <string>
using namespace std;
#define MA 20005
#define ll long long
struct Node{
    ll y;
    ll x1,x2;
    int flag;
    int id;
}eg[300005];
int tot;
int n,K;
ll temp[300005];
int cmp(Node a,Node b){
    if(a.y>b.y)
       return 0;
    if(a.y==b.y){
         if(a.flag==0 && b.flag==1)
           return 0;
         if(a.flag==-1 && (b.flag==1 || b.flag==0))
           return 0;
    }
    return 1;
}
int c[300020];
void add(int site,int val){
    while(site<tot+5){
        c[site]+=val;
        site+=site&(-site);
    }
}
int getsum(int site){
    int ret=0;
    while(site>0){
      ret+=c[site];
      site-=site&(-site);
    }
    return ret;
}
int sc[100005],has;
int main(){
  //  freopen("in.txt","r",stdin);
    int x,y,d;
    scanf("%d%d",&n,&K);
    tot=0;
    for(int i=0;i<n;++i){
        scanf("%d%d%d",&x,&y,&d);
        temp[tot++]=(ll)x+y+d;
        temp[tot++]=x+y;
        temp[tot++]=x+y-d;
        eg[i].y=y-x;
        eg[i].flag=0;
        eg[i].x1=x+y;
        eg[i].id=i+1;
      
        eg[i+n].y=y-x+d;
        eg[i+n].flag=-1;

        eg[i+2*n].y=y-x-d;
        eg[i+2*n].flag=1;
        eg[i+n].x1=eg[i+2*n].x1=x+y-d;
        eg[i+n].x2=eg[i+2*n].x2=(ll)x+y+d;
    }
    sort(temp,temp+tot);
    tot=unique(temp,temp+tot)-temp;
    int tt=3*n;
    for(int i=0;i<tt;++i){
        if(eg[i].flag==0){
           eg[i].x1=lower_bound(temp,temp+tot,eg[i].x1)-temp+1;
        }
        else {
           eg[i].x1=lower_bound(temp,temp+tot,eg[i].x1)-temp+1;
           eg[i].x2=lower_bound(temp,temp+tot,eg[i].x2)-temp+1;
        }
    }
    sort(eg,eg+3*n,cmp);
   // cout << tt << endl;
  //  for(int i=0;i<tt;++i)
  //     printf("flag=%d y=%lld x1=%lld x2=%lld id=%d\n",eg[i].flag,eg[i].y,eg[i].x1,eg[i].x2,eg[i].id);
    has=0;
    for(int i=0;i<tt;++i){
        if(eg[i].flag==0){
             int t=getsum(eg[i].x1);
             if(t>K){
                 sc[has++]=eg[i].id;
             }
        }
        else if(eg[i].flag==-1){
            add(eg[i].x1,-1);
            add(eg[i].x2+1,1);
        }
        else {
             add(eg[i].x1,1);
             add(eg[i].x2+1,-1);
        }
    }
    sort(sc,sc+has);
    printf("%d\n",has);
    if(has){
        printf("%d",sc[0]);
        for(int i=1;i<has;++i)
            printf(" %d",sc[i]);
        puts("");
    }
    return 0;
}


