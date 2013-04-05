#include <iostream>
#include<cstdio>
#include <cstring>
using namespace std;
const int maxn=1001000,maxm=5000000;
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
struct edge
{
	int y;
	int ne;
} h[maxm];
int hh;
int st[maxn];
void addedg(int x,int y)
{
	h[hh].y=y;
	h[hh].ne=st[x];
	st[x]=hh;
	hh++;
}
int n,m;
int maxs;
int s[maxn],ss;
int f[maxn];
int u[maxn],v[maxn],ttime;
void push(int* sta,int &head,int &tail,int k,int* a)
{
	while (head<tail&&a[sta[tail-1]]-sta[tail-1]<=a[k]-k) tail--;
	sta[tail++]=k;
}
int a[maxn*2];
int sta[maxn];
void duel(int p1,int p2)
{

	int i,k;
	int head=0,tail=0;
	int l=p2-p1;
	for (i=p1;i<p2;i++) a[i-p1]=f[s[i]];
	for (i=l;i<=l+l;i++) a[i]=a[i-l];

	for (i=l-(l/2);i<l;i++) push(sta,head,tail,i,a);
	for (i=l;i<l+l;i++)
	{
		maxs=max(maxs,a[i]+a[sta[head]]+i-sta[head]);
		while (head<tail&&sta[head]<i+1-(l/2)) head++;
		push(sta,head,tail,i,a);
	}
	k=-1;
	for (i=1;i<(l+1)/2;i++) k=max(k,i+a[i]);
	for (;i<l;i++) k=max(k,l-i+a[i]);
	f[s[p1]]=max(f[s[p1]],k);
}
void dfs1(int k,int fa)
{
	int i,t;
	u[k]=v[k]=++ttime;
	for (i=st[k];i!=-1;i=h[i].ne)
	{
		t=h[i].y;
		if (t==fa) continue;
		if (u[t]==0)
		{
			dfs1(t,k);
			v[k]=min(v[k],v[t]);
		}
		else
			v[k]=min(v[k],u[t]);
	}
}
int c[maxn];
void dfs2(int k,int fa)
{
	int i,j,t;
	s[ss++]=k;
	c[k]=1;
	for (i=st[k];i!=-1;i=h[i].ne)
	{
		t=h[i].y;
		if (t==fa) continue;
		if (u[k]<v[t]&&c[t]==0)
		{
			dfs2(t,k);
			maxs=max(maxs,f[k]+f[t]+1);  
			f[k]=max(f[k],f[t]+1);
		}
	}
	for (i=st[k];i!=-1;i=h[i].ne)
	{
		t=h[i].y;
		if (t==fa) continue;
		if (u[k]<=v[t]&&c[t]==0) dfs2(t,k);
	}
	for (i=st[k];i!=-1;i=h[i].ne)
	{
		t=h[i].y;
		if (t==fa) continue;
		if (c[t]==0)
			dfs2(t,k);
		else if (u[t]<u[k])
		{
			for (j=ss-1;s[j]!=t;j--);
			duel(j,ss);
		}
	}
	ss--;
}
void iin()
{
	int i,j,x,y;
	memset(st,-1,sizeof(st));
	hh=0;
	scanf("%d%d",&n,&m);
	for (i=0;i<m;i++)
	{
		scanf("%d",&j);
		scanf("%d",&x);
		while (--j>0)
		{
			scanf("%d",&y);
			addedg(x,y);
			addedg(y,x);
			x=y;
		}
	}
}
int main()
{
	freopen("t.in","r",stdin);
	iin();
	memset(u,0,sizeof(u));
	memset(v,0,sizeof(v));
	ttime=0;
	ss=0;
	memset(f,0,sizeof(f));
	memset(c,0,sizeof(c));
	maxs=-1;
	dfs1(1,-1);
	dfs2(1,-1);
	if (maxs==-1) maxs=0;
	printf("%d\n",maxs);
	return 0;
}
