#include <cstdio>
#define MAXN 101000
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define ROOT 1,1,n
#define NODE int t,int l,int r
#define LCHILD t*2,l,(l+r)/2
#define RCHILD t*2+1,(l+r)/2+1,r

struct Stuff
{
	int l,r;
	long long sum,m;
	bool e,marked;
	Stuff(bool c=true):e(c){sum=m=marked=0;}
	void set(long long x){sum=x;}
	void add(long long x){sum+=x*(r-l+1);}
} T[MAXN*4];
int n,m; 
int A[MAXN];

Stuff operator+(const Stuff &L,const Stuff &R)
{
	if(!L.e)return R; if(!R.e)return L;
	Stuff F;
	F.l=L.l; F.r=R.r;
	F.sum=L.sum+R.sum;
	return F;
}

void build(NODE)
{
	T[t].l=l; T[t].r=r;
	if(l==r){T[t].set(A[l]);return;}
	build(LCHILD); build(RCHILD);
	T[t]=T[2*t]+T[2*t+1];
}

void mark(int t,long long x)
{
	T[t].add(x);
	if(T[t].marked)
		T[t].m+=x;
	else
	{
		T[t].marked=true;
		T[t].m=x;
	}
}

void pushdown(int t)
{
	if(T[t].marked)
	{
		mark(t*2,T[t].m);mark(t*2+1,T[t].m);
		T[t].m=0;T[t].marked=false;
	}
}

void change(NODE,int a,int b,int x)
{
	if(l>b||a>r) return;
	if(a<=l&&r<=b){mark(t,x);return;}
	pushdown(t);
	change(LCHILD,a,b,x);
	change(RCHILD,a,b,x);
	T[t]=T[t*2]+T[t*2+1];
}

Stuff ask(NODE,int a,int b)
{
	if(l>b||a>r)return Stuff(false);
	if(a<=l&&r<=b)return T[t];
	pushdown(t);
	return ask(LCHILD,a,b)+ask(RCHILD,a,b);
}
int main()
{
	freopen("t.in","r",stdin);
	scanf("%d%d",&n,&m);
	FOR(i,1,n)scanf("%d",&A[i]);
	build(ROOT);
	FOR(i,1,m)
	{
		int a,b,x;
		char k;
		scanf("\n%c%d%d",&k,&a,&b);
		if(k=='C')
		{
			scanf("%d",&x);
			change(ROOT,a,b,x);
		}else printf("%lld\n",ask(ROOT,a,b).sum);
	}
}
