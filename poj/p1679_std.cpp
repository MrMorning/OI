#include<iostream>
#include <cstdio>
  #include<string.h>
  #include <algorithm>
  using namespace std;
  const int maxn=110;
  struct Edge
  {
  	int a,b,w;
  }edge[maxn*maxn];
  int tc;
  int n,m,a,b,c;
  int parent[maxn];
  int flag[maxn*maxn];
  int del[maxn],num;
  void init()
  {
  	memset(parent,-1,sizeof(parent));
  }
  int find(int a)
  {
  	if(parent[a]<0)
  		return a;
  	return parent[a]=find(parent[a]);
  }
  void Union(int a,int b)
  {
  	int pa=find(a),pb=find(b);
  	if(pa==pb)
  		return;
  	if(parent[pa]<parent[pb])
  	{
  		parent[pa]+=parent[pb];
  		parent[pb]=pa;
	}
  	else
  	{
  		parent[pb]+=parent[pa];
  		parent[pa]=pb;
  	}
  }
  bool cmp(Edge m1,Edge m2)
  {
  	return m1.w<m2.w;
  }
  int kruskal(int x)
  {
  	int num=0;
  	int sum=0;
  	int a,b;
  	int i;
  	memset(parent,-1,sizeof(parent));
  	for(i=0;i<m;i++)
  	{	
  		if(!flag[i])
  		{
  			a=edge[i].a,b=edge[i].b;
  			if(find(a)!=find(b))
  			{
  				if(x)
  					del[num]=i;
  				num++;
  				sum+=edge[i].w;
  				Union(a,b);
  				if(num==n-1)
  				{
  					return sum;
				}
  			}
		}
  	}
  	return 0;
  }
  void work()
  {
  	sort(edge,edge+m,cmp);
  	int ans=0;
  	int i;
  	num=0;
  	memset(flag,0,sizeof(flag));
  	ans=kruskal(1);
  	int tmp;
  	if(m>n-1)
  	{
  		for(i=0;i<n-1;i++)
  		{
  			flag[del[i]]=1;
  			//cout<<"del:"<<del[i]<<" "<<edge[i].a<<" "<<edge[i].b<<" "<<edge[i].w<<endl;
  			tmp=kruskal(0);
  			//printf("jason:%d\n",tmp);
  			if(ans==tmp)
  			{
  				//printf()
  				printf("Not Unique!\n");
  				return;
  			}
  			flag[del[i]]=0;
  		}
  	}
  	printf("%d\n",ans);
  }
  int main()
  {
	  freopen("t.in", "r", stdin);
  	scanf("%d",&tc);
  	while(tc--)
  	{
  		init();
  		scanf("%d%d",&n,&m);
  		int i;
  		for(i=0;i<m;i++)
  		{
  			scanf("%d%d%d",&a,&b,&c);
  			edge[i].a=a,edge[i].b=b,edge[i].w=c;
  		}
  		work();
  	}
  }
