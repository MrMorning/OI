#include <iostream>
#include <stdio.h>
using namespace std;
const int N=20000;
const int INF=0x7FFFFFFF;
struct headtype{int limit,w,p,i;} heap[100000];
int n,tot=0,water[N],limit[N],p[N],Swater=0,outtime[N];

void init(){
     scanf("%d",&n);
     for (int i=1;i<=n;i++)
       scanf("%d%d%d",&water[i],&limit[i],&p[i]);
}

inline int f(int t){
       return (heap[t].limit-heap[t].w);
}

void up(int k){
     while (k>1 && f(k/2)>f(k)){
           swap(heap[k],heap[k/2]);
           k/=2;
     }
}

void down(int k){
     while (k*2<=tot){
           int t;
           if (k*2+1<=tot && f(k*2+1)<f(k*2)) t=k*2+1;
                                         else t=k*2;
           if (f(t)<f(k)) swap(heap[t],heap[k]);
           k=t;
     }
}

void ins(int W,int L,int P,int i){
     tot++;
     heap[tot].w=W;
     heap[tot].limit=L;
     heap[tot].p=P;
     heap[tot].i=i;
     up(tot);
}

void del(){
     heap[1]=heap[tot];
     tot--;
     down(1);
}

void work(){
     int ans=INF,now=0,ansi=0;
     for (int i=n;i>=1;i--){
         Swater+=water[i];
         now+=p[i];
         ins(water[i]-Swater,limit[i],p[i],i);
         while (tot>0 && heap[1].w+Swater>heap[1].limit){
               now-=heap[1].p;
               outtime[heap[1].i]=i;
               del();
         }
         if (now<ans){
           ans=now;
           ansi=i;
         }
     }
     for (int i=ansi;i<=n;i++)
       if (outtime[i]<ansi) cout << i << endl;
}

int main(){
	freopen("t.in", "r", stdin);
    init();
    work();
}
