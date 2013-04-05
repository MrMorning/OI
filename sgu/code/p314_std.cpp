#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;

vector <pair <int,int> > g[10011],fg[10011];
int n,s,t;
int init()
{
	int m,i,k;
	scanf("%d%d%d%d%d",&n,&m,&k,&s,&t);
	for(i=0;i<m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g[a].push_back(make_pair(b,c));
		fg[b].push_back(make_pair(a,c));
	}
	return k;
}

int dist[10011];
priority_queue <pair <long long,int> > mindist;
void dij()
{
	int i;
	fill(dist+1,dist+1+n,1000000000);
	dist[t]=0;
	mindist.push(make_pair(0,t));
	while(!mindist.empty())
	{
		pair <long long,int> now=mindist.top();
		mindist.pop();
		now.first=-now.first;
		if(now.first!=dist[now.second])
			continue;
		for(vector <pair <int,int> > :: iterator j=fg[now.second].begin();j!=fg[now.second].end();++j)
			if(now.first+j->second<dist[j->first])
			{
				dist[j->first]=now.first+j->second;
				mindist.push(make_pair(-dist[j->first],j->first));
			}
	}
}

struct fh
{
	int data,index,dist,g_index,g_hash;
	fh *ch[4];
	fh(int da,int ind,int di)
	{
		data=da;
		index=ind;
		dist=di;
		g_index=-1;
		g_hash=0;
		ch[0]=ch[1]=ch[2]=ch[3]=NULL;
	}
	fh()
	{
		data=1000000000;
		index=-1;
		dist=0;
		g_index=-1;
		g_hash=0;
		ch[0]=ch[1]=ch[2]=ch[3]=NULL;
	}
}*small_heap[10011],*big_heap[10011];

fh *to_built[50011];
vector <pair <int,int> > :: iterator dist_father[10011];
void build_small_heap(int node)
{
	int hlen=0,i,j;
	to_built[1]=NULL;
	for(vector < pair <int,int> > :: iterator j=g[node].begin();j!=g[node].end();++j)
		if(j!=dist_father[node])
			to_built[++hlen]=new fh(j->second-dist[node]+dist[j->first],j->first,1);
	
	//merge
	for(i=hlen/2;i>=1;--i)
		for(j=i;j<=hlen/2;)
		{
			int j2=j*2,j21=j*2+1;
			if(to_built[j2]->data<to_built[j]->data&&(j21>hlen||to_built[j2]->data<=to_built[j21]->data))
			{
				swap(to_built[j],to_built[j2]);
				j=j2;
				continue;
			}
			if(j21<=hlen&&to_built[j21]->data<to_built[j]->data&&to_built[j21]->data<=to_built[j2]->data)
			{
				swap(to_built[j],to_built[j21]);
				j=j21;
				continue;
			}
			break;
		}
	
	//link
	for(i=1;i<=hlen/2;++i)
	{
		to_built[i]->ch[0]=to_built[i*2];
		if(i*2+1<=hlen)
			to_built[i]->ch[1]=to_built[i*2+1];
	}
	small_heap[node]=to_built[1];
}

fh *build_big_heap(int node,fh *now)
{
	if(small_heap[node]==NULL)
		return now;
	if(now==NULL||small_heap[node]->data<now->data)
	{
		small_heap[node]->ch[3]=now;
		return small_heap[node];
	}
	fh *ret=new fh;
	*ret=*now;
	if(ret->ch[2]==NULL||(ret->ch[3]!=NULL&&ret->ch[3]->dist>ret->ch[2]->dist))
	{
		ret->ch[2]=build_big_heap(node,ret->ch[2]);
		ret->dist=min(ret->ch[2]->dist,ret->ch[3]==NULL?0:ret->ch[3]->dist)+1;
		return ret;
	}
	else
	{
		ret->ch[3]=build_big_heap(node,ret->ch[3]);
		ret->dist=min(ret->ch[2]==NULL?0:ret->ch[2]->dist,ret->ch[3]->dist)+1;
		return ret;
	}
}

int hash[10011];
void build_tree(int i)
{
	hash[i]=1;
	if(dist_father[i]==g[i].end())
	{
		big_heap[i]=small_heap[i];
		return;
	}
	if(!hash[dist_father[i]->first])
		build_tree(dist_father[i]->first);
	big_heap[i]=build_big_heap(i,big_heap[dist_father[i]->first]);
}

vector <pair <int,int> > g2[1000011];
int glen;
void dfs_heap(fh *i)
{
	for(int j=0;j<4;++j)
		if(i->ch[j]!=NULL)
		{
			if(i->ch[j]->g_index==-1)
			{
				i->ch[j]->g_index=glen++;
				dfs_heap(i->ch[j]);
			}
			g2[i->g_index].push_back(make_pair(i->ch[j]->g_index,i->ch[j]->data-i->data));
		}
}
void dfs_heap2(fh *i)
{
	i->g_hash=1;
	if(big_heap[i->index]!=NULL)
		g2[i->g_index].push_back(make_pair(big_heap[i->index]->g_index,big_heap[i->index]->data));
	for(int j=0;j<4;++j)
		if(i->ch[j]!=NULL&&!i->ch[j]->g_hash)
			dfs_heap2(i->ch[j]);
}
void build_graph()
{
	int i;
	for(i=1;i<=n;++i)
	{
		vector <pair <int,int> > :: iterator j;
		for(j=g[i].begin();j!=g[i].end();++j)
			if(dist[j->first]==dist[i]-j->second)
				break;
		dist_father[i]=j;
	}
	for(i=1;i<=n;++i)
		build_small_heap(i);
	
	for(i=1;i<=n;++i)
		if(i!=t&&!hash[i])
			build_tree(i);
	
	for(i=1;i<=n;++i)
		if(big_heap[i]!=NULL&&big_heap[i]->g_index==-1)
		{
			big_heap[i]->g_index=glen++;
			dfs_heap(big_heap[i]);
		}
	for(i=1;i<=n;++i)
		if(big_heap[i]!=NULL&&!big_heap[i]->g_hash)
			dfs_heap2(big_heap[i]);
}

void get_ans(int k)
{
	int i;
	if(dist[s]>=1000000000)
	{
		for(i=1;i<=k;++i)
			printf("NO\n");
		return;
	}
	printf("%d\n",dist[s]);
	if(big_heap[s]==NULL)
	{
		for(i=2;i<=k;++i)
			printf("NO\n");
		return;
	}
	mindist.push(make_pair(-dist[s]-big_heap[s]->data,big_heap[s]->g_index));
	for(i=1;i<k&&!mindist.empty();++i)
	{
		pair <long long,int> now=mindist.top();
		mindist.pop();
		now.first=-now.first;
		if ( now.first>=1000000000)
			puts("NO");
		else
			printf("%lld\n",now.first);
		for(vector <pair <int,int> > :: iterator j=g2[now.second].begin();j!=g2[now.second].end();++j)
			mindist.push(make_pair(-(now.first+j->second),j->first));
	}
	for(;i<k;++i)
		printf("NO\n");
	return;
}

int main()
{
	freopen("t.in","r",stdin);
	freopen("t2.out","w",stdout);
	int k=init();
	dij();
	build_graph();
	get_ans(k);
	return 0;
}

