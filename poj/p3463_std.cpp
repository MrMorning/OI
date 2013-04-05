#include <iostream>
#include <stdio.h>
#include <string.h>
#define E 11111
#define N 1111*2
#define INF 0x7FFFFFFF/2
using namespace std;
struct gtp{int x,y,w,next;}g[E];
int ls[N],d[N],c[N],list[N],n,e,st,ed,zz[N];
struct headtpy{
	int a[N],tot;
	void up(int k){
		while (k>1 && d[a[k]]<d[a[k/2]]){
			swap(a[k],a[k/2]);
			zz[a[k]]=k; zz[a[k/2]]=k/2;
			k/=2;
		}
	}
	void down(int k){
		while (k*2<=tot){
			int t=k*2;
			if (t+1<=tot && d[a[t+1]]<d[a[t]]) t++;
			if (d[a[k]]>d[a[t]]){
				swap(a[k],a[t]);
				zz[a[k]]=k; zz[a[t]]=t;
				k=t;
			}
			else break;
		}
	}
	void ins(int locate){
		tot++;
		a[tot]=locate;
		zz[locate]=tot;
		up(tot);
	}
	void del(){
		a[1]=a[tot];
		tot--;
		down(1);
	}
}heap;

void init(){
	scanf("%d%d",&n,&e);
	memset(ls,0,sizeof(ls));
	memset(zz,0,sizeof(zz));
	for (int i=1;i<=e;i++){
		int x,y,w;
		scanf("%d%d%d",&g[i].x,&g[i].y,&g[i].w);
		g[i].next=ls[g[i].x]; ls[g[i].x]=i;
	}
	scanf("%d%d",&st,&ed);
	for (int i=1;i<=2*n;i++){
		d[i]=INF;
		c[i]=0;
	}
	d[st*2-1]=0; c[st*2-1]=1;
	heap.tot=0;
	for (int i=1;i<=2*n;i++) heap.ins(i);
}

inline void push(int td,int tc,int ty){
	if (td<d[ty*2-1]){
		d[ty*2]=d[ty*2-1];
		c[ty*2]=c[ty*2-1];
		heap.up(zz[ty*2]);
		d[ty*2-1]=td;
		c[ty*2-1]=tc;
		heap.up(zz[ty*2-1]);
	}
	else if (td==d[ty*2-1]) c[ty*2-1]+=tc;
	else if (td<d[ty*2]){
		d[ty*2]=td;
		c[ty*2]=tc;
		heap.up(zz[ty*2]);
	}
	else if (td==d[ty*2]) c[ty*2]+=tc;
}

void dijkstra(){
	while (heap.tot>0){
		int p=(heap.a[1]+1)/2;
		for (int t=ls[p];t!=0;t=g[t].next)
			push(d[heap.a[1]]+g[t].w,c[heap.a[1]],g[t].y);
		heap.del();
	}
	if (d[ed*2-1]+1==d[ed*2]) printf("%d\n",c[ed*2-1]+c[ed*2]);
	else printf("%d\n",c[ed*2-1]);
}

int main(){
	freopen("t.in","r",stdin);
	int tc;
	scanf("%d",&tc);
	for (int i=1;i<=tc;i++){
		init();
		dijkstra();
	}
}

