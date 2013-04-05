#include <iostream>
#include <cstdio>
using namespace std;
int color[1000001],Left[1000001],Right[1000001];
char order,str[10000];
int i,Count,temp,a,b,len,t,o,c;
void buildtree(int now,int l,int r){
	int mid;
	Left[now]=l;Right[now]=r;
	if(l==r) return;
	mid=(l+r)/2;
	buildtree(now*2,l,mid);
	buildtree(now*2+1,mid+1,r);
}
bool single(int x){
	return (((x-1)&(x))==0);
}
void insert(int now,int l,int r,int co){
	int mid;
	if(l<=Left[now]&&r>=Right[now]) {color[now]=co;return;}
	if(color[now]==co) return;
	if(single(color[now])) color[2*now]=color[2*now+1]=color[now];
	mid=(Left[now]+Right[now])/2;
	if(l<=mid) insert(now*2,l,r,co);
	if(r>mid) insert(now*2+1,l,r,co);
	color[now]=color[now*2]|color[now*2+1];
}
void search(int now,int l,int r){
	int mid;
	if((l<=Left[now]&&r>=Right[now])||single(color[now])) {Count|=color[now];return;}
	mid=(Left[now]+Right[now])/2;
	if(l<=mid) search(now*2,l,r);
	if(r>mid) search(now*2+1,l,r);
}
int ans(int c){
	int cnt=0;
	while (c>0) {cnt+=c%2;c/=2;}
	return cnt;
}
int main(){
	freopen("t.in","r",stdin);
	scanf("%d %d %d\n",&len,&t,&o);//cin>>len>>t>>o;
	buildtree(1,1,len);
	insert(1,1,len,1);
	for (i=1;i<=o;i++){
		gets(str);//cin>>order;
		switch (str[0]/*order*/){
			case 'C':
				sscanf(str,"%c %d %d %d",&order,&a,&b,&c);//printf("%d %d %d\n",a,b,c);cin>>a>>b>>c;
				if(a>b) {temp=a;a=b;b=temp;}
				insert(1,a,b,1<<(c-1));
				break;
			case 'P':
				sscanf(str,"%c %d %d",&order,&a,&b);//cin>>a>>b;
				if(a>b) {temp=a;a=b;b=temp;}
				Count=0;
				search(1,a,b);
				cout<<ans(Count)<<endl;
		}
	}
	return 0;
}
