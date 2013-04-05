#include <cstdio>
#define MAXN 1000010
#define FOR(i,s,t) for(int i=s;i<=t;i++)

struct Node
{
	int size,data,id,p,son[2];
}T[MAXN];
int root=0;
int nodeCnt;

void update(int x)
{
	T[x].size=T[T[x].son[0]].size+T[T[x].son[1]].size+1;
}

void rotate(int x,int w)
{
	int y=T[x].p;
	T[y].son[!w]=T[x].son[w];
	if(T[x].son[w])
		T[T[x].son[w]].p=y;
	T[x].p=T[y].p;
	if(T[y].p)
	{
		if(y==T[T[y].p].son[w])T[T[y].p].son[w]=x;
		else T[T[y].p].son[!w]=x;
	}
	T[x].son[w]=y;
	T[y].p=x;
	update(y);
	update(x);
}

void splay(int x,int y)
{
	while(T[x].p!=y)
	{
		if(T[T[x].p].p==y)
		{
			if(x==T[T[x].p].son[0])rotate(x,1);
			else rotate(x,0);
		}
		else
		{
			if(T[x].p==T[T[T[x].p].p].son[0])
			{
				if(x==T[T[x].p].son[0]){rotate(T[x].p,1);rotate(x,1);}
				else{rotate(x,0);rotate(x,1);}
			}
			else
			{
				if(x==T[T[x].p].son[0]){rotate(x,1);rotate(x,0);}
				else{rotate(T[x].p,0);rotate(x,0);}
			}
		}
	}
	if(y==0)root=x;
}

void insert(int id,int data)
{
	if(root==0)
	{
		root=++nodeCnt;
		T[root].id=id; T[root].data=data; T[root].size=1;
		return;
	}
	int x=root;
	while(1)
	{
		T[x].size++;
		if(data<T[x].data)
		{
			if(T[x].son[0])
				x=T[x].son[0];
			else break;
		}
		else 
		{
			if(T[x].son[1])
				x=T[x].son[1];
			else break;
		}
	}
	nodeCnt++;
	T[nodeCnt].data=data; T[nodeCnt].id=id;
	T[nodeCnt].p=x; T[nodeCnt].size=1;
	if(data<T[x].data) T[x].son[0]=nodeCnt;
	else T[x].son[1]=nodeCnt;
	splay(nodeCnt,0);
}

void remove(int x)
{
	splay(x,0);
	int y=T[x].son[0];
	while(T[y].son[1])y=T[y].son[1];
	int z=T[x].son[1];
	while(T[z].son[0])z=T[z].son[0];
	if(!y&&!z)
	{
	}
	else if(!(y&&z))
	{
		if(!y)
		{
			splay(z,0);
			T[z].son[0]=0;update(z);
		}
		else
		{
			splay(y,0);
			T[y].son[1]=0;update(y);
		}
	}
	else
	{
		splay(y,0);splay(z,y);
		T[z].son[0]=0;
		update(z); update(y);
	}
	T[x].size=T[x].data=T[x].id=T[x].son[0]=T[x].son[1]=0;
	if(x==root)root=0;
}

int find_rank(int v)
{
	int x=root;
	while(v!=T[T[x].son[0]].size+1)
		if(v<=T[T[x].son[0]].size)
			x=T[x].son[0];
		else
		{
			v-=T[T[x].son[0]].size+1;
			x=T[x].son[1];
		}
	splay(x,0);
	return x;
}

void test()
{
	insert(1,5);
	insert(2,6);
	insert(3,7);
	printf("%d\n",find_rank(3));
	remove(3);
	insert(4,10);
	printf("%d\n",find_rank(3));
}

int main()
{
	freopen("t.in","r",stdin);
	int k=1,n=0;
	while(k)
	{
		scanf("%d",&k);
		switch(k)
		{
			case 1:
				{
					int a,b;
					scanf("%d %d",&a,&b);
					n++;
					insert(a,b);
					break;
				}	
			case 2:
				{
					if(n==0)printf("0\n");
					else
					{
						int t=find_rank(n--);
						printf("%d\n",T[t].id);
						remove(t);
					}
					break;
				}
			case 3:
				{
					if(n==0)printf("0\n");
					else
					{
						int t=find_rank(1);
						printf("%d\n",T[t].id);
						remove(t);
						n--;
					}
					break;
				}
		}
		scanf("\n");
	}
	//test();
}

