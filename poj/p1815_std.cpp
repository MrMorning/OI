#include<iostream>
#include<cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

#define inf 1000000000

#define maxn 550

struct Edge{

	int v,val,next;

}e[500000];

int box[maxn];

int n,m,S,T;

int map[205][205],cut[maxn];

int pre[maxn],used[maxn],d[maxn],f[maxn*maxn];

int q[maxn],head,end,id[maxn];

int min(int x,int y)

{

	return x<y?x:y;

}

int maxflow()

{

	int i,j,ret=0,x,y;

	memset(f,0,sizeof(f));

	while(1)

	{

		memset(used,0,sizeof(int)*(n+n+10));

		head=0;end=0;

		q[end++]=S;

		used[S]=1;

		d[S]=inf;

		while(head<end && !used[T])

		{

			x=q[head++];

			for(i=box[x];i!=-1;i=e[i].next)

			{

				y=e[i].v;

				if((y<=n&&cut[y]==1)||(y>n && cut[y-n]==1))

					continue;

				if(!used[y] && e[i].val>f[i])

				{

					used[y]=1;

					pre[y]=x;

					id[y]=i;

					q[end++]=y;

					d[y]=min(d[x],e[i].val-f[i]);

				}

			}

		}

		if(!used[T])

			break;

		ret+=d[T];

		for(y=T;y!=S;y=pre[y])

		{

			i=id[y];

			f[i]+=d[T];

			if(i<m)

				f[i+m]=-f[i];

			else

				f[i-m]=-f[i];

		}

	}

	return ret;

}

int main()

{
	freopen("t.in", "r", stdin);

	int i,j,x,y;

	while(scanf("%d%d%d",&n,&S,&T)==3)

	{

		memset(box,-1,sizeof(box));

		m=n*n+5;

		int k=0;



		for(i=1;i<=n;i++)

		{

			for(j=1;j<=n;j++)

			{

				scanf("%d",&map[i][j]);

				if(i!=j && map[i][j]==1)

				{

					e[k].v=j;

					e[k].val=inf;

					e[k].next=box[i+n];

					box[i+n]=k;

					k++;

				}

			}

			if(i==S || i==T)

			{

				e[k].v=i+n;

				e[k].val=inf;

				e[k].next=box[i];

				box[i]=k;

				k++;

			}

			else

			{

				e[k].v=i+n;

				e[k].val=1;

				e[k].next=box[i];

				box[i]=k;

				k++;

			}

		}

		if(map[S][T]==1)

		{

			printf("NO ANSWER!\n");

			continue;

		}

		memset(cut,0,sizeof(cut));

		int flow,preflow,ans=0;

		preflow=maxflow();

		for(i=1;i<=n;i++)

		{

			if(i==S || i==T)

				continue;

			cut[i]=1;

			flow=maxflow();

			if(flow<preflow)

			{

				ans++;

				preflow=flow;

			}

			else

				cut[i]=0;

			if(flow==0)

				break;

		}

		printf("%d\n",ans);

		if(ans)

		{

			for(i=1;i<=n;i++)

				if(cut[i])

					printf("%d ",i);

			printf("\n");

		}

	}

	return 0;

}
