#include <cstdio>
#include <algorithm>
#include <cstring>
#define INF 0x3f3f3f3f
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define MAXN 10100
#define NODE int t,int l,int r
#define LCHILD t*2,l,(l+r)/2
#define RCHILD t*2+1,(l+r)/2+1,r
#define ROOT 1,1,n

using namespace std;

struct Stuff
{
	int l,r,maxl,maxr,maxs,minl,minr,mins,sum;
	bool e;
	Stuff(bool c=true):e(c){l=r=0;maxl=maxr=maxs=-INF;minl=minr=mins=INF;sum=0;}
	void set(int x){maxl=maxr=maxs=minl=minr=mins=sum=x;}
} T[MAXN*4];
int n,m;
int A[MAXN];

Stuff operator+(const Stuff &L,const Stuff &R)
{
	if(!L.e)return R; if(!R.e)return L;
	Stuff P;
	P.l=L.l; P.r=R.r;
	P.maxl=max(L.sum+R.maxl,L.maxl);
	P.maxr=max(R.sum+L.maxr,R.maxr);
	P.maxs=max(L.maxr+R.maxl,max(L.maxs,R.maxs));

	P.minl=min(L.sum+R.minl,L.minl);
	P.minr=min(R.sum+L.minr,R.minr);
	P.mins=min(L.minr+R.minl,min(L.mins,R.mins));
	P.sum=L.sum+R.sum;
	return P;
}

void build(NODE)
{
	T[t].l=l;T[t].r=r;
	if(l==r){T[t].set(A[l]);return;}
	build(LCHILD);build(RCHILD);
	T[t]=T[2*t]+T[2*t+1];
}

Stuff ask(NODE,int a,int b)
{
	if(l>b||a>r)return Stuff(false);
	if(a<=l&&r<=b)return T[t];
	return ask(LCHILD,a,b)+ask(RCHILD,a,b);
}

int main()
{
	freopen("t.in","r",stdin);
	int testnum;
	scanf("%d",&testnum);
	while(testnum--)
	{
		scanf("%d",&n);
		FOR(i,1,n)T[i]=Stuff();
		FOR(i,1,n)scanf("%d",&A[i]);
		build(ROOT);
		scanf("%d",&m);
		FOR(i,1,m)
		{
			int ans=-INF,x1,y1,x2,y2,s[5];
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(y1<x2)ans=ask(ROOT,x1,y2).sum-min(0,ask(ROOT,x1,y1-1).minl)-min(0,ask(ROOT,x2+1,y2).minr);
			else
			{
				s[1]=ask(ROOT,x2,y1).sum+max(0,ask(ROOT,x1,x2-1).maxr)+max(0,ask(ROOT,y1+1,y2).maxl);
				s[2]=ask(ROOT,x1,x2).maxr+max(0,ask(ROOT,x2+1,y1).maxl);
				s[3]=ask(ROOT,x2,y1).maxr+max(0,ask(ROOT,y1+1,y2).maxl);
				s[4]=ask(ROOT,x2,y1).maxs;;
				FOR(k,1,4)ans=max(ans,s[k]);
			}
			printf("%d\n",ans);
		}
	}
}
