#include<cstdio>
#include<map>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAX=200+10;
const int NUM=100000+100;

int n,m,q;
double p;
int rec[MAX][MAX];

map<int,int>change;
int tot;

int num[MAX*MAX];
int f[MAX][MAX];
struct rex
{
	int x1,x2,y1,y2;
	int answer,num;
}r[NUM];
int answer[NUM];

int swap(int &a,int& b)
{
	int t=a;a=b;b=t;
}

void calc_above_p(int k)
{
	int sum,i,j;
	memset(f,0,sizeof f);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
		{
			f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]\
					+(rec[i][j]==k);
		}
	for(i=1;i<=q;++i)
	{
		sum=f[r[i].x2][r[i].y2]+f[r[i].x1-1][r[i].y1-1]\
			-f[r[i].x1-1][r[i].y2]-f[r[i].x2][r[i].y1-1];
		r[i].answer+=sum*sum;
	}
}
int x[MAX*MAX][MAX],y[MAX*MAX][MAX],num_node[MAX*MAX];

void add(int xx,int yy)
{
	//printf("%d %d\n",xx,yy);
	int c=rec[xx][yy],i;
	x[c][++num_node[c]]=xx;y[c][num_node[c]]=yy;
}

struct dui
{
	int x1,y1,x2,y2;
}pa[MAX*MAX*100];
int num_pair;

int compare(const rex& a,const rex& b){return a.x1<b.x1;}
int cmp(const dui& a,const dui& b){return a.x1<b.x1;}

int tree[MAX][MAX][MAX];
int lowbit(int i)
{
	return i&(-i);
}

void insert(int x2,int y1,int y2)
{
	int i,j,k;
	for(i=x2;i<=n+1;i+=lowbit(i))
	{
		for(j=y1;j<=m+1;j+=lowbit(j))
			for(k=y2;k<=m+1;k+=lowbit(k))
			{
				++tree[i][j][k];
			}
	}
}

int ask(int x2,int y1,int y2)
{
	int i,j,k;
	int answer=0;
	for(i=x2;i>=1;i-=lowbit(i))
		for(j=y1;j>=1;j-=lowbit(j))
			for(k=y2;k>=1;k-=lowbit(k))
			{
				//printf("%d %d %d\n",i,j,k);
				answer+=tree[i][j][k];
			}
	return answer;
}

int main()
{
	freopen("t.in","r",stdin);
	int i,j,k;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
		{
			scanf("%d",&rec[i][j]);
			if(!change[rec[i][j]])change[rec[i][j]]=++tot;
			rec[i][j]=change[rec[i][j]];
		}
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			++num[rec[i][j]];
	scanf("%d",&q);
	int kk=m*n+q;
	int l1=(int)(log((double)n)/log(2.0));
	int l2=(int)(log((double)m)/log(2.0));
	for(i=1;i<=q;++i)
	{
		r[i].num=i;r[i].answer=0;
		scanf("%d %d %d %d",&r[i].x1,&r[i].y1,&r[i].x2,&r[i].y2);
		if(r[i].x2<r[i].x1)swap(r[i].x1,r[i].x2);
		if(r[i].y2<r[i].y1)swap(r[i].y1,r[i].y2);
	}
	int sum;
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			if(num[rec[i][j]]*num[rec[i][j]]*l1*l1*l2<kk)
				add(i,j);
	//n-p.x1<=n-r.x1 p.x2<=r.x2 m-p.y1<=m-r.y1 p.y2<=r.y2
	for(k=1;k<=tot;++k) {
		if(num[k]*num[k]*l1*l1*l2>=kk)
		{
			calc_above_p(k);
		}else 
		{
			for(i=1;i<=num_node[k];++i)
				for(j=1;j<=num_node[k];++j)
				{
					++num_pair;

					if(x[k][i]<x[k][j])
					{
						pa[num_pair].x1=n-x[k][i]+1;
						pa[num_pair].x2=x[k][j];
					}else 
					{
						pa[num_pair].x1=n-x[k][j]+1;
						pa[num_pair].x2=x[k][i];
					}
					if(y[k][i]<y[k][j])
					{
						pa[num_pair].y1=m-y[k][i]+1;
						pa[num_pair].y2=y[k][j];
					}else 
					{
						pa[num_pair].y1=m-y[k][j]+1;
						pa[num_pair].y2=y[k][i];
					}
					//printf("%d %d %d %d\n",x[k][i],y[k][i],x[k][j],y[k][j]);
				}
		}//return 0;
	}
	for(i=1;i<=q;++i)
	{
		r[i].x1=n-r[i].x1+1;
		r[i].y1=m-r[i].y1+1;
	}
	sort(pa+1,pa+num_pair+1,cmp);
	sort(r+1,r+q+1,compare);

	int nowpa=1,t;
	for(i=1;i<=q;++i)
	{
		while(pa[nowpa].x1<=r[i].x1&&nowpa<=num_pair)
		{
			insert(pa[nowpa].x2,pa[nowpa].y1,pa[nowpa].y2);
			//printf("%d %d %d\n",pa[nowpa].x2,pa[nowpa].y1,pa[nowpa].y2);
			++nowpa;
		}
		t=ask(r[i].x2,r[i].y1,r[i].y2);
		//printf("%d %d %d\n",r[i].x2,r[i].y1,r[i].y2);
		//printf("%d\n",t);
		r[i].answer+=t;
	}

	for(i=1;i<=q;++i)
		answer[r[i].num]=r[i].answer;
	for(i=1;i<=q;++i)
		printf("%d\n",answer[i]);
}
