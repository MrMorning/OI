#include <cstdio>
#include <cstring>
#define MAXN 200050
#define MAXLEN MAXN * 4
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int cnt = 0;

struct Node
{
	int l,r,mid;
	int val;
} T[MAXLEN];

void build(int i,int l,int r)
{
	T[i].l = l;
	T[i].r = r;
	T[i].mid = (l+r)>>1;
	if(l == r) return;
	build(i<<1,l,T[i].mid);
	build(i*2+1,T[i].mid+1,r);
}

void insert(int i,int idx,int val)
{
	if(T[i].l == T[i].r)
	{
		T[i].val = val;
		return;
	}
	if(idx <= T[i].mid)
		insert(i << 1,idx,val);
	else
		insert(i * 2 +1,idx,val);
	T[i].val = max(T[i*2].val,T[i*2+1].val);
}

int ask(int i,int l,int r)
{
	if(l > r) return 0;
	if(T[i].l >= l && T[i].r <= r)
		return T[i].val;
	int t1=ask(i*2,l,min(T[i].mid,r));
	int t2=ask(i*2+1,max(T[i].mid+1,l),r);
	return max(t1,t2);
}

int main()
{
	freopen("t.in","r",stdin);
	memset(T,0xff,sizeof(T));
	int M,D;
	scanf("%d%d\n",&M,&D);
	build(1,1,M);
	int n = 0, t = 0;
	for(int i = 1; i <= M; i++)
	{
		char opt;
		int x;
		scanf("%c %d\n",&opt,&x);
		if(opt == 'A')
			insert(1,++n,(x%D+t%D)%D);
		else
			printf("%d\n",t = ask(1,n-x+1,n));
	}
}
