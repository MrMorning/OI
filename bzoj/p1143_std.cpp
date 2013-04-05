#include"stdio.h"
#include"string.h"
 
#define inf 100000000
 
struct node
{
   int s,e,l,next;
}edge[30000];
 
int start[300],g[110][110],dist[500],queue[300],cnt,n,S,T;
bool flag[300];
void Add_Edge(int a,int b,int c)
{
   edge[++cnt].e=b;
   edge[cnt].s=a;
   edge[cnt].l=c;
   edge[cnt].next=start[a];
   start[a]=cnt;
   return;
}
 
void Dfs(int k)
{
   if(flag[k]==true)return;
   flag[k]=true;
   for(int i=1;i<=n;i++)
      if(g[k][i]==true)Dfs(i);
   return;
}
 
int Bfs()
{
   int u,open=0,closed=0;
   memset(dist,-1,sizeof(dist));
   dist[S]=0;
   while(open>=closed)
   {
      u=queue[closed++];
      for(int temp=start[u];temp!=0;temp=edge[temp].next)
         if(dist[edge[temp].e]==-1&&edge[temp].l>0)
         {
            dist[edge[temp].e]=dist[u]+1;
            queue[++open]=edge[temp].e;
         }
   }
   return dist[T]+1;
}
 
int Min(int a,int b)
{
   return a<=b?a:b;
}
 
int Dinic(int now,int left)
{
   if(now==T)return left;
   int aug=0,temp,k,add;
   for(temp=start[now];temp!=0;temp=edge[temp].next)
      if(dist[edge[temp].e]==dist[now]+1&&edge[temp].l>0)
         if(add=Dinic(edge[temp].e,Min(left-aug,edge[temp].l)))
         {
            aug+=add;
            k=(temp&1)?temp+1:temp-1;
            edge[temp].l-=add;
            edge[k].l+=add;
         }
   if(!aug)dist[now]=-1;
   return aug;
}
    
int Max_Flow()
{
   int flow=0,left;
   while(Bfs())
      while(left=Dinic(S,inf))flow+=left;
   return flow;
}
 
int main()
{
   int m,a,b;
   scanf("%d %d",&n,&m);
   S=0,T=2*n+1;
   for(int i=1;i<=m;i++)
      scanf("%d %d",&a,&b),g[a][b]=true;
   for(int i=1;i<=n;i++)
   {
      Dfs(i),flag[i]=false;
      for(int j=1;j<=n;j++)
         if(flag[j]==true)
            Add_Edge(j+n,i,0),Add_Edge(i,j+n,inf);
      memset(flag,false,sizeof(flag));
   }
   for(int i=1;i<=n;i++)
   {
      Add_Edge(S,i,1),Add_Edge(i,S,0);
      Add_Edge(i,i+n,0),Add_Edge(i+n,i,inf);
      Add_Edge(i+n,T,1),Add_Edge(T,i+n,0);
   }
   printf("%d\n",n-Max_Flow());
   return 0;
}
