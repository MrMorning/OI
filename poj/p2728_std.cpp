#include<iostream>
#include <cstdio>
#include<cmath>
using namespace std;
#define inf 1000000000
int n,p[1005][2],h[1100];
double dis[1100];
int used[1100];
double prime(double mid)
{
	int i,j,u;
	double sum=0,mn;
	for(i=1;i<=n;i++)
	{
		dis[i]=inf;
		used[i]=0;
	}
	dis[1]=0;
	for(i=0;i<n;i++)
	{
		mn=inf;
		for(j=1;j<=n;j++)
		{
			if(!used[j] && dis[j]<mn)
			{
				mn=dis[j];
				u=j;
			}
		}
		used[u]=1;
		sum+=mn;
		for(j=1;j<=n;j++)
		{
			double len=sqrt(0.0+(p[j][0]-p[u][0])*(p[j][0]-p[u][0])+(p[j][1]-p[u][1])*(p[j][1]-p[u][1]));
			double val=abs(h[j]-h[u])-mid*len;
			if(j!=u && !used[j] && dis[j]>val)
			{
				dis[j]=val;
			}
		}
	}
	return sum;
}
int main()
{
	freopen("t.in", "r", stdin);
	int i,j;
	while(scanf("%d",&n),n)
	{
		for(i=1;i<=n;i++)
			scanf("%d%d%d",&p[i][0],&p[i][1],&h[i]);
		double l,r,mid,key;
		l=0;r=1000;
		while(r-l>0.0001)
		{
			mid=(l+r)/2;
			if(prime(mid)>0)
			{
				key=mid;
				l=mid;
			}
			else
				r=mid;
		}
		printf("%0.3f\n",key);
	}
	return 0;
}
