#include <cstdio>
#include <algorithm>
#define ROOT 1,1,N
#define NODE int t,int l,int r
#define LCH t*2,l,(l+r)/2
#define RCH t*2+1,(l+r)/2+1,r
#define FOR(i,s,t) for(int i=s;i<=t;i++)
#define MAXN 50100
#define INF 0x3fffffff
using namespace std;

int N,M,A[MAXN];
struct Stuff
{
	int maxl,maxr,maxs,sum,l,r;
	bool e;
	Stuff(bool c=true):e(c){maxl=maxr=maxs=sum=-INF;}
	void set(int x){maxl=maxr=maxs=sum=x;}
	bool full()const{return sum==maxs;};
} T[MAXN<<2];

Stuff operator+(const Stuff &L,const Stuff &R)
{
	if(!L.e)return R; if(!R.e)return L;
	Stuff F;
	F.maxs=max(L.maxr+R.maxl,max(L.maxs,R.maxs));
	F.maxl=max(L.sum+R.maxl,L.maxl);
	F.maxr=max(R.sum+L.maxr,R.maxr);
	F.sum=L.sum+R.sum;
	F.l=L.l; F.r=R.r;
	return F;
}

void build(NODE)
{
	T[t].l=l; T[t].r=r;
	if(l==r){T[t].set(A[l]);return;}
	build(LCH); build(RCH);
	T[t]=T[t*2]+T[t*2+1];
}

void change(NODE,int i,int val)
{
	if(r<i||l>i) return;
	if(T[t].l==T[t].r&&T[t].l==i)
	{T[t].set(val);return;}
	change(LCH,i,val);
	change(RCH,i,val);
	T[t]=T[t*2]+T[t*2+1];
}

Stuff ask(NODE,int a,int b)
{
	if(r<a||b<l) return Stuff(false);
	if(a<=l&&r<=b)
		return T[t];
	Stuff s1=ask(LCH,a,b);
	Stuff s2=ask(RCH,a,b);
	return s1+s2;
}



int main()
{
	freopen("t.in","r",stdin);
	scanf("%d",&N);
	FOR(i,1,N)scanf("%d",&A[i]);
	build(ROOT);
	scanf("%d",&M);
	while(M--)
	{
		int k,x,y;
		scanf("%d%d%d",&k,&x,&y);
		if(k==0)
			change(ROOT,x,y);
		else
			printf("%d\n",ask(ROOT,x,y).maxs);
	}
}
