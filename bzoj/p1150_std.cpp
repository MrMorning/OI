#include"stdio.h"

long long ans=0,pos[100010],a[100010],heap[100010],total;
int n,K,num[100010]={0},l[100010]={0},r[100010]={0},mid;

int Swap(long long *a,long long *b)
{
   long long t=*a;
   *a=*b,*b=t;
   return 0;
}

int Exchange(int a,int b)
{
   Swap(&heap[a],&heap[b]);
   Swap(&pos[heap[a]],&pos[heap[b]]);
   return 0;
}

int Down(int k)
{
   int x;
   while((k<<1)<=total)
   {
      x=k<<1;
      if(x<total&&a[heap[x]]>a[heap[x+1]])x++;
      if(a[heap[x]]<a[heap[k]])Exchange(x,k);
         else break;
      k=x;
   }
   return 0;
}

int Up(int k)
{
   int x;
   while(k!=1)
   {
      x=k>>1;
      if(a[heap[x]]>a[heap[k]])Exchange(x,k);
         else break;
      k=x;
   }
   return 0;
}

int Delete(int a)
{
   Exchange(a,total);
   total--;
   Up(a),Down(a);
   return 0;
}
   
int main()
{
	freopen("t.in", "r", stdin);
   scanf("%d %d",&n,&K);
   for(int i=1;i<=n;i++)
      scanf("%d",&num[i]);
   for(int i=1;i<=n+1;i++)
   {
      heap[i]=i,pos[i]=i,a[i]=num[i]-num[i-1];
      l[i]=i-1,r[i]=i+1;
   }
   a[1]=a[n+1]=1000000000;
   total=n+1;
   for(int i=total/2;i>0;i--)Down(i);
   while(K--)
   {
      mid=heap[1];
      ans+=a[mid];
      int c=l[mid],d=r[mid];
      r[c]=r[d];
      l[r[d]]=c;
      Delete(pos[d]);
      Delete(pos[mid]);
      a[c]+=a[d]-a[mid];
      Down(pos[c]),Up(pos[c]);
   }
   printf("%lld\n",ans);
   return 0;
}
