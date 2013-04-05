#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define MAXN 100000
#define TREE int t,int l,int r
#define LCHILD t*2,l,(l+r)/2
#define RCHILD t*2+1,(l+r)/2+1,r
#define ROOT 1,1,n

using namespace std;

int n,m;

struct sinfo
{
	int sum,maxl,maxr,maxs,size;
	void set(bool x){sum=maxl=maxr=maxs=x?size:0;}
	sinfo():size(1){}
	bool full()const{return sum==size;}
};

sinfo operator+(const sinfo &L,const sinfo &R)
{
	sinfo F;
	F.size=L.size+R.size;
	F.sum=L.sum+R.sum;
	F.maxl=L.full()?L.sum+R.maxl:L.maxl;
	F.maxr=R.full()?R.sum+L.maxr:R.maxr;
	F.maxs=max(L.maxr+R.maxl,max(L.maxs,R.maxs));
	return F;

}

struct Info
{
	sinfo I[2];
	bool e;
	Info(bool _e=true):e(_e){}
	void set(bool c){FOR(i,0,1) I[i].set(i==c);}
} T[MAXN<<2];

Info operator+(const Info &L,const Info &R)
{
	if(!L.e)return R;if(!R.e)return L;
	Info F; FOR(i,0,1) F.I[i]=L.I[i]+R.I[i];
	return F;
}

int A[MAXN],M[MAXN<<2]={};

void mark(int t,int m)
{
	if(m==3){swap(T[t].I[1],T[t].I[0]);M[t]=3-M[t];}
	else{T[t].set(m-1);M[t]=m;}
}

void pushdown(int t)
{
	if(M[t]){mark(t*2,M[t]);mark(t*2+1,M[t]);M[t]=0;}
}

void build(TREE)
{
	if(l==r){T[t].set(A[l]);return;}
	build(LCHILD); build(RCHILD);
	T[t]=T[t*2]+T[t*2+1];
}
Info ask(TREE,int a,int b)
{
	if(a>r||b<l)return Info(false);
	if(a<=l&&r<=b) return T[t];
	pushdown(t);
	return ask(LCHILD,a,b)+ask(RCHILD,a,b);
}

void change(TREE,int a,int b,int m)
{
	if(a>r||b<l) return;
	if(a<=l&&r<=b){mark(t,m);return;}
	pushdown(t);
	change(LCHILD,a,b,m);change(RCHILD,a,b,m);
	T[t]=T[t*2]+T[t*2+1];
}


int main()
{
	freopen("t.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i = 1,x; i <= n; i++)
	{
		scanf("%d",&x);
		A[i]=x;
	}
	build(1,1,n);
	for(int i = 1,opt,a,b; i <= m; i++)
	{
		scanf("%d%d%d",&opt,&a,&b);
		a++; b++;
		switch(opt)
		{
			case 0: case 1: case 2: change(ROOT,a,b,opt+1); break;
			case 3: printf("%d\n",ask(ROOT,a,b).I[1].sum); break;
			case 4: printf("%d\n",ask(ROOT,a,b).I[1].maxs); break;
		}
	}
}
