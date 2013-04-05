#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <utility>
#define MAXN 50010
#define INF 0x3f3f3f3f
#define MP make_pair
#define fr first
#define sc second
#define ABS(x) ((x)>0?(x):-(x))
using namespace std;
typedef pair<int,int> PII;
typedef pair<PII,int> PIII;

int h[MAXN],hx[MAXN],hn[MAXN],bb[MAXN],bh[MAXN],bhx[MAXN],bhn[MAXN],L[MAXN],R[MAXN],cost[MAXN],ans[MAXN],n,N;
//hx = hmax hn = hmin

struct SegmentTree {
#define MAXM 65536
	int val[MAXM*2],t0,t1,t2;
	SegmentTree(){ memset(val,0x3f,sizeof(val)); }
	void modify(int i,int NewVal) {
		val[i+=N]=NewVal;
		int t=i>>1;
		while (t)
			val[t]=min(val[i],val[i^1]),
			i=t, t>>=1;
	}
	int query(int s,int t) {
		int ret=INF;
		if (s<=t) {
			for (s=s+N-1,t=t+N+1;s^t^1;s>>=1,t>>=1) {
				if (~s&1) ret=min(ret,val[s^1]);
				if ( t&1) ret=min(ret,val[t^1]);
			}
		}
		return ret;
	}
	int getVal(int x) {
		return val[x+N];
	}
};
SegmentTree T1,T2,T3,T4,T5,T6,T7,T8,T9;

PII b[MAXN];
PIII tmp[MAXN*3];

int main() {
	freopen("t.in","r",stdin);

	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",&h[i]);
	for (int i=2;i<n;++i) cost[i]=ABS(h[i]-h[i-1])+ABS(h[i]-h[i+1]);
	cost[1]=ABS(h[1]-h[2]);
	cost[n]=ABS(h[n]-h[n-1]);
	
	for (int i=1;i<=n;++i) b[i]=MP(h[i],i);
	sort(b+1,b+n+1);
	b[0].fr=INF;
	int tot=0;
	for (int i=1;i<=n;++i) {
		if (b[i].fr!=b[i-1].fr) R[tot]=i-1, L[++tot]=i;
		bh[b[i].sc]=tot, bb[b[i].sc]=i;
	}
	R[tot]=L[tot+1]=R[tot+1]=n+1;
	
	for (int i=2;i<n;++i)
		if (h[i-1]>h[i+1])
			hx[i]=h[i-1], bhx[i]=bh[i-1], hn[i]=h[i+1], bhn[i]=bh[i+1];
		else
			hx[i]=h[i+1], bhx[i]=bh[i+1], hn[i]=h[i-1], bhn[i]=bh[i-1];
	for (N=1;N+1<=n;N<<=1);
	
	tot=0;
	for (int i=2;i<n;++i)
		tmp[++tot]=MP(MP(hn[i],-1),i),
		tmp[++tot]=MP(MP(h [i], 0),i),
		tmp[++tot]=MP(MP(hx[i], 1),i);
	sort(tmp+1,tmp+tot+1);
	
	for (int i=tot;i>0;--i) {
		int t=tmp[i].sc;
		if (tmp[i].fr.sc==1) {
			T4.modify(bb[t],-cost[t]-h[t]*2+hx[t]-hn[t]);
			T5.modify(bb[t],-cost[t]+hx[t]-hn[t]);
			T6.modify(bb[t],-cost[t]+h[t]*2+hx[t]-hn[t]);
		}
		else if (tmp[i].fr.sc==-1) {
			T4.modify(bb[t],INF);
			T5.modify(bb[t],INF);
			T6.modify(bb[t],INF);
			T1.modify(bb[t],-cost[t]-h[t]*2+hx[t]+hn[t]);
			T2.modify(bb[t],-cost[t]+hx[t]+hn[t]);
			T3.modify(bb[t],-cost[t]+h[t]*2+hx[t]+hn[t]);
		}
		else {
			int t0,t1,t2;
			t2=T1.getVal(bb[t  ]); if (t2!=INF) T1.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T1.query(1,R[bhn[t]-1])-cost[t]-h[t]*2+hx[t]+hn[t]);
			if (t2!=INF) T1.modify(bb[t  ],t2);
			
			t0=T2.getVal(bb[t-1]); if (t0!=INF) T2.modify(bb[t-1],INF);
			t1=T2.getVal(bb[t+1]); if (t1!=INF) T2.modify(bb[t+1],INF);
			t2=T2.getVal(bb[t  ]); if (t2!=INF) T2.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T2.query(L[bhn[t]],R[bhx[t]])-cost[t]-h[t]*2+hx[t]-hn[t]);
			if (t0!=INF) T2.modify(bb[t-1],t0);
			if (t1!=INF) T2.modify(bb[t+1],t1);
			if (t2!=INF) T2.modify(bb[t  ],t2);
			
			t2=T3.getVal(bb[t  ]); if (t2!=INF) T3.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T3.query(L[bhx[t]+1],n)-cost[t]-h[t]*2-hx[t]-hn[t]);
			if (t2!=INF) T3.modify(bb[t  ],t2);
			
			t2=T4.getVal(bb[t  ]); if (t2!=INF) T4.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T4.query(1,R[bhn[t]-1])-cost[t]+hx[t]+hn[t]);
			if (t2!=INF) T4.modify(bb[t  ],t2);
			
			t0=T5.getVal(bb[t-1]); if (t0!=INF) T5.modify(bb[t-1],INF);
			t1=T5.getVal(bb[t+1]); if (t1!=INF) T5.modify(bb[t+1],INF);
			t2=T5.getVal(bb[t  ]); if (t2!=INF) T5.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T5.query(L[bhn[t]],R[bhx[t]])-cost[t]+hx[t]-hn[t]);
			if (t0!=INF) T5.modify(bb[t-1],t0);
			if (t1!=INF) T5.modify(bb[t+1],t1);
			if (t2!=INF) T5.modify(bb[t  ],t2);
			
			t2=T6.getVal(bb[t  ]); if (t2!=INF) T6.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T6.query(L[bhx[t]+1],n)-cost[t]-hx[t]-hn[t]);
			if (t2!=INF) T6.modify(bb[t  ],t2);
		}
	}
	
	for (int i=1;i<=tot;++i) {
		int t=tmp[i].sc;
		if (tmp[i].fr.sc==1) {
			T7.modify(bb[t],-cost[t]-h[t]*2-hx[t]-hn[t]);
			T8.modify(bb[t],-cost[t]-hx[t]-hn[t]);
			T9.modify(bb[t],-cost[t]+h[t]*2-hx[t]-hn[t]);
		}
		else if (tmp[i].fr.sc==0) {
			int t0,t1,t2;
			t2=T7.getVal(bb[t  ]); if (t2!=INF) T7.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T7.query(1,R[bhn[t]-1])-cost[t]+h[t]*2+hx[t]+hn[t]);
			if (t2!=INF) T7.modify(bb[t  ],t2);
			
			t0=T8.getVal(bb[t-1]); if (t0!=INF) T8.modify(bb[t-1],INF);
			t1=T8.getVal(bb[t+1]); if (t1!=INF) T8.modify(bb[t+1],INF);
			t2=T8.getVal(bb[t  ]); if (t2!=INF) T8.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T8.query(L[bhn[t]],R[bhx[t]])-cost[t]+h[t]*2+hx[t]-hn[t]);
			if (t0!=INF) T8.modify(bb[t-1],t0);
			if (t1!=INF) T8.modify(bb[t+1],t1);
			if (t2!=INF) T8.modify(bb[t  ],t2);
			
			t2=T9.getVal(bb[t  ]); if (t2!=INF) T9.modify(bb[t  ],INF);
			ans[t]=min(ans[t],T9.query(L[bhx[t]+1],n)-cost[t]+h[t]*2-hx[t]-hn[t]);
			if (t2!=INF) T9.modify(bb[t  ],t2);
		}
	}
	
	long long tt=0;
	for (int i=2;i<=n;++i) tt+=ABS(h[i]-h[i-1]);
	for (int i=2;i<n;++i) {
		int t = -cost[1]-cost[i];
		swap(h[1],h[i]);
		t+=ABS(h[2]-h[1])+ABS(h[i+1]-h[i])+ABS(h[i]-h[i-1]);
		ans[1]=min(ans[1],t); ans[i]=min(ans[i],t);
		swap(h[1],h[i]);
	}
	for (int i=2;i<n;++i) {
		int t = -cost[n]-cost[i];
		swap(h[n],h[i]);
		t+=ABS(h[n]-h[n-1])+ABS(h[i]-h[i-1])+ABS(h[i+1]-h[i]);
		ans[n]=min(ans[n],t); ans[i]=min(ans[i],t);
		swap(h[n],h[i]);
	}
	
	for (int i=2;i<n-1;++i) {
		int j=i+1, t=-cost[i]-cost[j];
		swap(h[i],h[j]);
		t+=ABS(h[j+1]-h[j])+ABS(h[j]-h[j-1])+ABS(h[i+1]-h[i])+ABS(h[i]-h[i-1]);
		ans[i]=min(ans[i],t); ans[j]=min(ans[j],t);
		swap(h[i],h[j]);
	}
	
	int t=-cost[1]-cost[n];
	swap(h[1],h[n]);
	t+=ABS(h[2]-h[1]);
	if (n!=2) t+=ABS(h[n]-h[n-1]);
	ans[1]=min(ans[1],t); ans[n]=min(ans[n],t);
	
	for (int i=1;i<=n;++i) printf("%lld\n",ans[i]+tt);
}
