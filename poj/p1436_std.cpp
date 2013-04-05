#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn=20000;
typedef struct seg
{
	int l,r,pos;
	bool operator<(const seg &p)const
	{
		return pos<p.pos;
	}    
}seg;
seg p[maxn];
vector<int> v[maxn];
int use[maxn];    
typedef struct node
{
	int l,r,c;    
}node;
node tree[4*maxn];     
void build(int k,int l,int r)
{
	tree[k].l=l;tree[k].r=r;tree[k].c=-1;
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(k*2,l,mid);build(k*2+1,mid+1,r); 
}
void down(int k)
{
	if(tree[k].c!=-1){tree[k*2].c=tree[k*2+1].c=tree[k].c;tree[k].c=-1;} 
}    
void query(int k,int l,int r,int id)
{
	if(tree[k].c!=-1)
	{
		if(use[tree[k].c]!=id){v[tree[k].c].push_back(id);use[tree[k].c]=id;}
		return ;              
	}    
	if(tree[k].l==tree[k].r)return ;
	down(k);
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)query(k*2,l,r,id);
	if(r>mid)query(k*2+1,l,r,id);   
}
void insert(int k,int l,int r,int id)
{
	if(l<=tree[k].l&&tree[k].r<=r){tree[k].c=id;return ;}
	down(k);
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)insert(k*2,l,r,id);
	if(r>mid)insert(k*2+1,l,r,id);      
}        
int main()
{
	freopen("t.in", "r", stdin);
	int i,j,k,t,w,n,test,l,r,ans,id;
	scanf("%d",&test);
	while(test--)
	{
		build(1,0,16000);
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			scanf("%d%d%d",&p[i].l,&p[i].r,&p[i].pos);
			p[i].l<<=1;p[i].r<<=1;v[i].clear();            
		}       
		sort(p,p+n);fill(use,use+n,-1);
		for(i=0;i<n;i++)
		{
			query(1,p[i].l,p[i].r,i);
			insert(1,p[i].l,p[i].r,i);            
		}            
		ans=0; 
		for(i=0;i<n;i++)for(j=0;j<v[i].size();j++)//暴力统计 
		{ 
			k=v[i][j];
			for(t=0;t<v[i].size();t++)for(w=0;w<v[k].size();w++)if(v[i][t]==v[k][w])ans++;
		}
		printf("%d\n",ans);        
	} 
	return 0;
}
