# include <iostream>
#include <cstdio>
using namespace std;

const int MAXP = 30005;//最多元素
int par[MAXP] ; //parent数组 代表集合
int C[MAXP][2]; //0- 到父亲节点数   1- 集合元素个数
int find_set(int x)//查找x所在的集合 x可能会在集合x中
{
	int tx;
	if(x!=par[x]){
		tx=par[x];
		par[x]=find_set(par[x]);//路径压缩
		C[x][0]+=C[tx][0];//路径压缩的时候 加上他父亲的到（父亲） 节点的个数
	}
	return par[x];
}
int union_set(int x,int y)
{
	x=find_set(x),y=find_set(y);
	if(x==y)return x;
	C[y][0]+=C[x][1];//头上就多了 x集合中元素的个数
	C[x][1]+=C[y][1];//x集合多了y集合的个数
	return (par[y]=x);
}
int main()
{
	freopen("t.in","r",stdin);
	int a,b,T;
	for(a=0;a<MAXP;a++)C[a][0]=0,C[a][1]=1,par[a]=a;
	char ss[5];
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",ss);
		if(ss[0]=='M')
		{
			scanf("%d%d",&a,&b);//a在b集合的头上
			union_set(a,b);
		}
		else
		{
			scanf("%d",&a);
			b=find_set(a);
			printf("%d\n",C[b][1]-C[a][0]-1);
		}
	}
	return 0;
}
