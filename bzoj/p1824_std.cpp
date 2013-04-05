#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
const int MAX_N=5000;
struct Point{
	int x,y;
	bool operator<(const Point&p)const{
		return x<p.x;
	}
	bool operator==(const Point&p)const{
		return x==p.x&&y==p.y;
	}
	bool operator!=(const Point&p)const{
		return x!=p.x||y!=p.y;
	}
	void read(){
		scanf("%d%d",&x,&y);
	}
	void write(){
		cout<<"("<<x<<","<<y<<")";
	}
	void refX(){x=-x;}
	void refY(){y=-y;}
};

int nPs;
int pCnt;
Point ps[MAX_N];
void inputData(){
	scanf("%d",&pCnt);
	rep(i,pCnt)
		ps[i].read();
}

Point RU[MAX_N],LU[MAX_N],LD[MAX_N],RD[MAX_N];
int nRU,nLU,nLD,nRD;

	void orderIt(Point qs[MAX_N],int nQs){
		if(nQs>1&&qs[0].x>qs[1].x)
			reverse(qs,qs+nQs);
	}

void doit(Point RU[MAX_N],int&nRU){
	if(!nRU)return;
	orderIt(RU,nRU);

	int cRU=0;
	RU[cRU++]=RU[0];
	for(int i=1;i<nRU;i++){
		if(RU[i].y<RU[cRU-1].y)
			RU[cRU++]=RU[i];
	}

	nRU=cRU;
}

	void refX(Point qs[MAX_N],int nQs){
		rep(i,nQs)
			qs[i].refX();
	}

	void refY(Point qs[MAX_N],int nQs){
		rep(i,nQs)
			qs[i].refY();
	}

int countMinus(Point RU[MAX_N],int nRU,Point LU[MAX_N],int nLU,
		Point LD[MAX_N],int nLD,Point RD[MAX_N],int nRD){
	int minus=0;
	int atLU=nLU-1,atRD=-1;
	int LUtoLD=nLD,RDtoLD=nLD-1;
	for(int atRU=0;atRU<nRU;atRU++){
		Point p=RU[atRU];
		while(atLU>=0&&LU[atLU].y>p.y)
			--atLU;
		while(atRD+1<nRD&&RD[atRD+1].x<p.x)
			++atRD;
		int left;
		if(atLU>=0&&LU[atLU].y<p.y){
			Point np=LU[atLU];
			int&cLD=LUtoLD;
			while(cLD>0&&LD[cLD-1].x>np.x)
				--cLD;
			if(cLD<nLD&&LD[cLD].x>np.x)
				left=cLD;
			else
				left=nLD;
		} else {
			left=0;
		}

		int right;

		if(atRD>=0&&RD[atRD].x<p.x){
			Point np=RD[atRD];
			int&cLD=RDtoLD;
			while(cLD>=0&&LD[cLD].y<np.y)
				--cLD;
			if(cLD>=0&&LD[cLD].y>np.y)
				right=cLD;
			else
				right=-1;
		} else {
			right=nLD-1;
		}
		if(left<=right){
			minus+=right-left+1;
		}
	}
	return minus;
}

void count(const Point&o,int&add,int&minus){
	add=0;minus=0;
	nRU=nLU=nLD=nRD=0;
	rep(i,nPs){
		Point p=ps[i];
		if(p==o)continue;
		int a=p.x>o.x;int b=p.y>o.y;
		if(a&&b){//RU
			RU[nRU++]=p;
		} else if(!a&&b){//LU
			LU[nLU++]=p;
		} else if(!a&&!b){//LD
			LD[nLD++]=p;
		} else {//RD
			RD[nRD++]=p;
		}
	}

	//RU
	{
		doit(RU,nRU);
		orderIt(RU,nRU);
	}
	//LU
	{
		refX(LU,nLU);
		doit(LU,nLU);
		refX(LU,nLU);
		orderIt(LU,nLU);
	}
	//LD
	{
		refX(LD,nLD);
		refY(LD,nLD);
		doit(LD,nLD);
		refX(LD,nLD);
		refY(LD,nLD);
		orderIt(LD,nLD);
	}
	//RD
	{
		refY(RD,nRD);
		doit(RD,nRD);
		refY(RD,nRD);
		orderIt(RD,nRD);
	}

	add=nRU+nLU+nLD+nRD;

	minus=0;
	{
		minus+=countMinus(RU,nRU,LU,nLU,LD,nLD,RD,nRD);
	}
	{
		refX(RU,nRU);orderIt(RU,nRU);
		refX(LU,nLU);orderIt(LU,nLU);
		refX(LD,nLD);orderIt(LD,nLD);
		refX(RD,nRD);orderIt(RD,nRD);
		minus+=countMinus(LU,nLU,RU,nRU,RD,nRD,LD,nLD);
	}
}

void work(){
	nPs=0;
	int curAns=0;
	long long sA=0,sB=0;
	rep(i,pCnt){
		int add,minus;
		Point p=ps[i];
		count(p,add,minus);
		ps[nPs++]=p;
		int at=nPs-1;
		while(at>0&&ps[at].x<ps[at-1].x)
			swap(ps[at],ps[at-1]),--at;
		curAns+=add;curAns-=minus;
		if(i%2==0)
			sA+=curAns;
		else
			sB+=curAns;
		//printf("*%d\n", curAns);
	}

	cout<<sA<<" "<<sB<<endl;
}

void solve(){
	inputData();
	work();
}

int main(){
	freopen("t.in", "r", stdin);
	solve();
}
