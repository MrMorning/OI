#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define NODE int t,int l,int r
#define LCHILD t*2,l,(l+r)/2
#define RCHILD t*2+1,(l+r)/2+1,r
#define ROOT 1,1,n
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define MAXN 200010
#define INF 0x3f3f3f3f
#define UNDEF -INF

using namespace std;

struct Stuff
{
	int l,r,maxs,maxnow,tag,mtag;
	bool e,marked;
	Stuff(bool c=true):e(c){maxs=maxnow=tag=mtag=UNDEF;marked=false;}
	void set(int x){maxs=maxnow=x;}
} T[MAXN*4];
int A[MAXN],last[MAXN],exist[MAXN*2];
struct Query
{
	int s,t,i;
}Q[MAXN];
int n,m;

Stuff operator+(const Stuff&L,const Stuff&R)
{
	if(!L.e)return R;if(!R.e)return L;
	Stuff F;
	F.l=L.l; F.r=R.r;
	F.maxnow=max(L.maxnow,R.maxnow);
	F.maxs=max(F.maxs,max(F.maxnow,max(L.maxs,R.maxs)));
	return F;
}

void build(NODE)
{
	T[t].l=l;T[t].r=r;
	if(l==r){T[t].set(A[l]);return;}
	build(LCHILD);build(RCHILD);
	T[t]=T[t*2]+T[t*2+1];
}
void mark(int t,int x=UNDEF)
{
	if(x==UNDEF)
	{
		//if(T[t].marked)
		//{
			T[t].mtag=max(T[t].mtag,T[t/2].mtag+T[t].tag);
			T[t].tag+=T[t/2].tag;
		/*}
		else
		{
			T[t].tag=T[t/2].tag;
			T[t].mtag=T[t/2].mtag;
		}*/
	}
	else
	{
		if(T[t].marked)
		{
			T[t].tag+=x;
			T[t].mtag=max(T[t].tag,T[t].mtag);
		}
		else
			T[t].tag=T[t].mtag=x;
	}
	T[t].marked=true;
	T[t].maxs=max(T[t].maxs,T[t].maxnow+T[t/2].mtag);
	T[t].maxnow+=T[t/2].tag;
}


void pushdown(int t)
{
	if(T[t].marked)
	{
		T[2*t].mtag=max(T[2*t].mtag,T[t].mtag+T[2*t].tag);
		T[2*t].tag+=T[t].tag;
		T[2*t].maxs=max(T[2*t].maxs,T[2*t].maxnow+T[t].mtag);
		T[2*t].maxnow+=T[t].tag;

		T[2*t+1].mtag=max(T[2*t+1].mtag,T[t].mtag+T[2*t+1].tag);
		T[2*t+1].tag+=T[t].tag;
		T[2*t+1].maxs=max(T[2*t].maxs,T[2*t+1].maxnow+T[t].mtag);
		T[2*t+1].maxnow+=T[t].tag;

		T[t].tag=T[t].mtag=T[t].marked=0;
	}
}

void change(NODE,int a,int b,int x)
{
	if(b<l||a>r) return;
	if(a<=l&&r<=b){mark(t,x);return;}
	pushdown(t);
	change(LCHILD,a,b,x);
	change(RCHILD,a,b,x);
	T[t]=T[t*2]+T[t*2+1];
}

Stuff ask(NODE,int a,int b)
{
	if(b<l||a>r) return Stuff(false);
	if(a<=l&&r<=b) return T[t];
	pushdown(t);
	return ask(LCHILD,a,b)+ask(RCHILD,a,b);
}

int comp(const void*a,const void*b)
{return ((Query*)a)->t-((Query*)b)->t;}

int main()
{
	freopen("t.in","r",stdin);
	scanf("%d",&n);
	FOR(i,1,n)
	{
		scanf("%d",&A[i]);
		last[i]=exist[A[i]+100000];exist[A[i]+100000]=i;
	}
	scanf("%d",&m);
	FOR(i,1,m){scanf("%d%d",&Q[i].s,&Q[i].t);Q[i].i=i;}
	qsort(Q+1,m,sizeof(Query),comp);
	build(ROOT);
	int p=0,ans[MAXN];
	FOR(i,1,m)
	{
		while(p<Q[i].t)
		{
			p++;
			change(ROOT,last[p]+1,p-1,A[p]);
		}
		ans[Q[i].i]=ask(ROOT,Q[i].s,Q[i].t).maxs;
	}
	FOR(i,1,m)printf("%d\n",max(ans[i],0));
}
