#include "stdio.h"

int f[100005],level[100005];
int test,n,m,ra,rb;
char c[2];
void creat_set()
{
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		level[i]=0;
	}
} 

int find_set(int s)
{
	int temp;
	if(s!=f[s])
	{
		temp=f[s];        
		f[s]=find_set(f[s]);
		level[s]=(level[temp]+level[s])%2;  // 更新其与依附节点的关系
	}  
	return f[s];
}        

void Union(int a,int b)
{

	f[rb]=ra;
	level[rb]=(level[a]-level[b]+1)%2;   //修改b所在集合接到a所在集合后其根结点与新根结点的关系

}       

int main()
{
	freopen("t.in","r",stdin);
	int a,b;
	scanf("%d",&test);
	while(test--)
	{
		scanf("%d%d",&n,&m);
		creat_set();
		for(int i=1;i<=m;i++)
		{
			scanf("%s%d%d",c,&a,&b);
			ra=find_set(a);
			rb=find_set(b);
			if(c[0]=='D')
				Union(a,b);
			else
			{

				if(ra!=rb)
					printf("Not sure yet.\n"); 
				else if((level[a]+level[b])%2==0)
					printf("In the same gang.\n"); 
				else
					printf("In different gangs.\n");            
			}
		}
	}   
	return  0;
}              
