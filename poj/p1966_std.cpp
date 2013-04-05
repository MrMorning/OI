#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inf 200
struct gtp{int x,y,next,c,op;}g[10000];
int n,m,e,a[50][50],S,T,flow;
int ls[100],cur[100],fa[100],d[100],num[100];

void relabel(int k){
	int mm=n+n;
	cur[k]=ls[k];
	for (int t=ls[k];t!=0;t=g[t].next)
		if (g[t].c && d[g[t].y]<mm) mm=d[g[t].y];
	d[k]=mm+1;
}    

void change(){
	int nf=inf;
	for (int i=T;i!=S;i=g[fa[i]].x)
		if (g[fa[i]].c<nf) nf=g[fa[i]].c;
	for (int i=T;i!=S;i=g[fa[i]].x){
		g[fa[i]].c-=nf;
		g[g[fa[i]].op].c+=nf;
	}
	flow+=nf;
}    

void sap(){
	flow=0;
	memset(d,0,sizeof(d));
	memset(num,0,sizeof(num));
	for (int i=0;i<n+n;i++) cur[i]=ls[i];
	num[0]=n+n;
	int i=S;
	while (d[0]<n+n){
		for (;cur[i]!=0;cur[i]=g[cur[i]].next)
			if (g[cur[i]].c && d[g[cur[i]].y]+1==d[i]) break;
		if (!cur[i]){
			if (--num[d[i]]==0) break;
			relabel(i);
			num[d[i]]++;
			if (i!=S) i=g[fa[i]].x;
		}
		else{
			fa[g[cur[i]].y]=cur[i];
			i=g[cur[i]].y;
			if (i==T){
				change();
				i=S;
			}    
		}    
	}    
}    

inline void addedge(int x,int y,int c){
	e++;
	g[e].x=x; g[e].y=y; g[e].c=c; g[e].op=e+1; g[e].next=ls[x]; ls[x]=e;
	e++;
	g[e].x=y; g[e].y=x; g[e].c=0; g[e].op=e-1; g[e].next=ls[y]; ls[y]=e;
}    

int main(){
	freopen("t.in", "r", stdin);
	while (scanf("%d%d",&n,&m)!=EOF){
		memset(a,0,sizeof(a));
		for (int i=1;i<=m;i++){
			int x,y;
			scanf(" (%d,%d)",&x,&y);
			a[x][y]=1; a[y][x]=1;
		}
		int ans=inf;
		for (S=n;S<2*n;S++)
			for (T=0;T<n;T++)
				if (S-n!=T){
					e=0;
					memset(ls,0,sizeof(ls));
					for (int i=0;i<n;i++)
						for (int j=0;j<n;j++)
							if (a[i][j]) addedge(i+n,j,inf);
					for (int i=0;i<n;i++) addedge(i,i+n,1);
					sap();
					if (flow<ans) ans=flow;
				}
		if (ans>n) ans=n;
		printf("%d\n",ans);
	}
	return 0;
}
