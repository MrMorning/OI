#include <cstdio>
#include <cstring>
#include <cstdlib>
struct gtp{int x,y,w,op,next;}g[810];
int n,m,p,dis;
int w[405][405],fa[66],depth[66],lx[405],ly[405],link[405],ls[66];
bool cx[405],cy[405];

inline void swap(int &x,int &y){x=x^y; y=x^y; x=x^y;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}

void input(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&g[i].x,&g[i].y,&g[i].w);
		g[i].next=ls[g[i].x];
		ls[g[i].x]=i;
		g[i].op=i+m;
	}
	for (int i=m+1;i<=2*m;i++){
		g[i].x=g[i-m].y;
		g[i].y=g[i-m].x;
		g[i].w=g[i-m].w;
		g[i].next=ls[g[i].x];
		ls[g[i].x]=i;
		g[i].op=i-m;
	}
}

void buildtree(int p){
	for (int t=ls[p];t;t=g[t].next)
		if ((t<n || g[t].op<n) && t!=g[fa[p]].op){
			fa[g[t].y]=t;
			depth[g[t].y]=depth[p]+1;
			buildtree(g[t].y);
		}
}

void buildgraph(){
	memset(w,0,sizeof(w));
	int i,x,y,Fa;
	for (i=n;i<=m;i++){
		x=g[i].x; y=g[i].y;
		while (y!=x){
			if (depth[x]>depth[y]) swap(x,y);
			Fa=fa[y];
			if (Fa>=n) Fa=g[Fa].op;
			w[Fa][i-n+1]=max(0,g[Fa].w-g[i].w);
			y=g[fa[y]].x;
		}
	}
	p=max(n-1,m-n+1);
}

bool find(int i){
	cx[i]=true;
	int q;
	for (int j=1;j<=p;j++)
		if (lx[i]+ly[j]==w[i][j] && !cy[j]){
			cy[j]=true;
			q=link[j];
			link[j]=i;
			if (!q || find(q)) return true;
			link[j]=q;
		}
		else if (!cy[j]) dis=min(dis,lx[i]+ly[j]-w[i][j]);
	return false;
}

void KM(){
	int i,j;
	for (i=1;i<=p;i++)
		for (j=1;j<=p;j++)
			if (w[i][j]>lx[i])
				lx[i]=w[i][j];
	for (i=1;i<=p;i++){
		for (;;){
			for (j=1;j<=p;j++) cx[j]=false;
			for (j=1;j<=p;j++) cy[j]=false;
			dis=0x7FFFFFFF;
			if (find(i)) break;
			for (j=1;j<=p;j++) if (cx[j]) lx[j]-=dis;
			for (j=1;j<=p;j++) if (cy[j]) ly[j]+=dis;
		}
	}
}

void output(){
	/*for (int i=1;i<=p;i++) g[i].w-=lx[i];
	for (int i=1;i<=p;i++) g[i+n-1].w+=ly[i];
	for (int i=1;i<=m;i++)
		printf("%d\n",g[i].w);*/
	int res = 0;
	for(int i = 1; i <= p; i ++)
		res += lx[i] + ly[i];
	printf("%d\n", res);
}

int main(){
	freopen("t.in", "r", stdin);
	input();
	buildtree(1);
	buildgraph();
	KM();
	output();
}
