#include<cstdio>
#include<algorithm>
#include<functional>
#include"memory.h"
using namespace std;
const int N = 1<<16;
const int M = 10005;
struct in{
	unsigned int  x,y;
	int b;
	bool flg;
	bool operator()(const in&L,const in&R){
		return L.x<R.x;
	}
}s[2*M];
int ans=0;
unsigned int w,h,inx[M];
class segTree
{
	struct Node{
		unsigned int bgn,end;
		int sum,maxSum;
	}q[N];
	public:
	int get() const { return q[1].maxSum; }
	void build(unsigned int n){ build__(0,n,1); }
	void push(unsigned int a,unsigned int b,int x){ push__(a,b,x,1); }
	private:
	void build__(unsigned int a,unsigned int b,int now){
		q[now].bgn=a; q[now].end=b;
		q[now].sum = q[now].maxSum = 0;
		if(a<b){
			build__(a,(a+b)/2,2*now);
			build__((a+b)/2+1,b,2*now+1);
		}
	}
	void push__(unsigned int a,unsigned int b,int x,int now){
		if(a<=q[now].bgn&&q[now].end<=b){
			q[now].sum += x;  q[now].maxSum += x;
		}else if(q[now].bgn<q[now].end){
			if(a<=(q[now].bgn+q[now].end)/2)push__(a,b,x,2*now);
			if(b>(q[now].bgn+q[now].end)/2)push__(a,b,x,2*now+1);
			q[now].sum = q[now*2].sum + q[now*2+1].sum;
			q[now].maxSum = max(q[2*now].maxSum,q[2*now].sum+q[2*now+1].maxSum);
		}
	}
}sg;
int bins(int n,unsigned int k){
	int l = 0,r = n;
	while(l<r){
		int md=(l+r)>>1;
		if(inx[md]<k)l=md+1;
		else r=md;
	}
	return l;
}
int main()
{
	freopen("t.in", "r", stdin);
	int n,m,t;
	while(scanf("%d%u%u",&n,&w,&h)==3)
	{
		m = t = ans = 0;
		for(int i=0;i<n;++i){
			unsigned int x,y;int b;
			scanf("%u%u%d",&x,&y,&b);
			inx[m++] = y; inx[m++] = y+h;
			s[t].x=x;s[t].y=y;s[t].b=b;s[t].flg=true;++t;
			s[t].x=x+w;s[t].y=y;s[t].b=b;s[t].flg=false;++t;
		}
		sort(s,s+t,in());
		sort(inx,inx+m);
		int res = -1;
		for(int i=0;i<m;++i){//离散化
			if(i<n-1&&inx[i]==inx[i+1])continue;
			inx[++res] = inx[i];
		}
		sg.build(res);
		for(int i=0;i<t;++i){
			int a=bins(res,s[i].y),b=bins(res,s[i].y+h);
			if(s[i].flg){//插入
				sg.push(a,a,s[i].b);
				sg.push(b,b,-s[i].b);
			}else {//删除
				sg.push(a,a,-s[i].b);
				sg.push(b,b,s[i].b);
			}
			//if(i<t-1/*&&s[i].x!=s[i+1].x*/)
				ans=max(ans,sg.get());
		}
		printf("%d\n",ans);
	}
	return 0;
}

