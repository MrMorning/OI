#include<cstdio>
using namespace std;
#define MAX 50005
#define INF 9223372036854775807
int n,e;
struct node{
	int e,d;
	int next;
	void set(int t1,int t2,int t3){
		e=t1;
		d=t2;
		next=t3;
	}
};
node a[MAX*3];
int b[MAX];
int s;
int w[MAX];
long long dis[MAX];
int heap[MAX];
int heap_size;
int pos[MAX];
bool use[MAX];
void swap(int i,int j){
	pos[heap[i]]=j;
	pos[heap[j]]=i;
	int temp=heap[i];
	heap[i]=heap[j];
	heap[j]=temp;
}
void up_update(int k){
	while(k>1){
		if(dis[heap[k/2]]>dis[heap[k]]){
			swap(k/2,k);
			k=k/2;
		}
		else break;
	}
}
void down_update(int k){
	int large=k;
	if(2*k<heap_size&&dis[heap[2*k]]<dis[heap[large]])large=2*k;
	if(2*k+1<heap_size&&dis[heap[2*k+1]]<dis[heap[large]])large=2*k+1;
	if(large==k)return ;
	swap(large,k);
	down_update(large);
}
void insert(int k){
	pos[k]=heap_size;
	heap[heap_size++]=k;
	up_update(heap_size-1);
}
int getmax(){
	int ret=heap[1];
	swap(1,--heap_size);
	down_update(1);
	return ret;
}
void solve(){
	if(n==0){
		printf("0\n");
		return;
	}
	dis[1]=0;
	heap_size=1;
	insert(1);
	long long ans=0;
	int r=0;
	while(heap_size>1){
		int k=getmax();
		ans=ans+dis[k]*w[k];
		use[k]=true;
		r++;
		pos[k]=0;
		int i=b[k];
		while(i){
			int j=a[i].e,c=a[i].d;
			if(!use[j]&&dis[j]>dis[k]+c){
				dis[j]=dis[k]+c;
				if(pos[j]==0)insert(j);
				else up_update(pos[j]);
			}
			i=a[i].next;
		}
	}
	if(r<n)printf("No Answer\n");
	else printf("%lld\n",ans);
}
void addedge(int x,int y,int d){
	a[s].set(y,d,b[x]);
	b[x]=s++;
}
int main(){
	freopen("t.in", "r", stdin);
	int t;
	scanf("%d",&t);
	while(t--){
		s=1;
		scanf("%d%d",&n,&e);
		int i;
		for(i=1;i<=n;i++){
			b[i]=0;
			pos[i]=0;
			use[i]=false;
			dis[i]=INF;
			scanf("%d",&w[i]);
		}
		for(i=0;i<e;i++){
			int x,y,d;
			scanf("%d%d%d",&x,&y,&d);
			addedge(x,y,d);
			addedge(y,x,d);
		}
		solve();
	}
	return 0;
}
